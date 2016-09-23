#pragma once

#include <cpp_odbc/statement.h>
#include <cpp_odbc/multi_value_buffer.h>
#include <turbodbc/field.h>
#include <turbodbc/description.h>

namespace turbodbc {

/**
 * @brief This interface represents a single parameter of a query
 */
class parameter {
public:
	/**
	 * @brief Create a new parameter, binding an internal buffer to the statement
	 * @param statement The statement for which to bind a buffer
	 * @param one_based_index One-based parameter index for bind command
	 * @param buffered_rows Number of rows for which the buffer should be allocated
	 * @param desription Description concerning data type of parameter
	 */
	parameter(cpp_odbc::statement const & statement, std::size_t one_based_index, std::size_t buffered_rows, std::unique_ptr<description const> description);

	/**
	 * @brief Set the value of the parameter associated with the given row to the given value
	 * @param row_index Index of the row for which the value is set
	 * @param value The value which is set
	 */
	void set(std::size_t row_index, turbodbc::nullable_field const & value);

	/**
	 * @brief Retrieve a reference to the internal buffer
	*/
	cpp_odbc::multi_value_buffer & get_buffer();

	~parameter();
private:
	std::unique_ptr<description const> description_;
	cpp_odbc::multi_value_buffer buffer_;
};


/**
 * @brief Move the buffer element contained in the given row_index to the first row (with index 0)
 * @param param Parameter for which to perform the operation
 * @param row_index Index of the row whose value is copied
 */
void move_to_top(parameter & param, std::size_t row_index);


}

#include <DB/DataTypes/FieldToDataType.h>
#include <DB/DataTypes/DataTypeFixedString.h>

#include <DB/Columns/ColumnString.h>
#include <DB/Columns/ColumnConst.h>
#include <DB/Columns/ColumnFixedString.h>


namespace DB
{


template <> ColumnPtr ColumnConst<String>::convertToFullColumn() const
{
	if (!data_type || dynamic_cast<const DataTypeString *>(&*data_type))
	{
		ColumnString * res = new ColumnString;
		ColumnPtr res_ptr = res;
		ColumnString::Offsets_t & offsets = res->getOffsets();
		ColumnUInt8::Container_t & vec = dynamic_cast<ColumnVector<UInt8> &>(res->getData()).getData();

		size_t string_size = data.size() + 1;
		size_t offset = 0;
		offsets.resize(s);
		vec.resize(s * string_size);

		for (size_t i = 0; i < s; ++i)
		{
			memcpy(&vec[offset], data.data(), string_size);
			offset += string_size;
			offsets[i] = offset;
		}

		return res_ptr;
	}
	else if (const DataTypeFixedString * type = dynamic_cast<const DataTypeFixedString *>(&*data_type))
	{
		size_t n = type->getN();

		if (data.size() > n)
			throw Exception("Too long value for " + type->getName(), ErrorCodes::TOO_LARGE_STRING_SIZE);

		ColumnFixedString * res = new ColumnFixedString(n);
		ColumnPtr res_ptr = res;
		ColumnUInt8::Container_t & vec = dynamic_cast<ColumnVector<UInt8> &>(res->getData()).getData();

		vec.resize(n * s, 0);
		size_t offset = 0;

		for (size_t i = 0; i < s; ++i)
		{
			memcpy(&vec[offset], data.data(), data.size());
			offset += n;
		}

		return res_ptr;
	}
	else
		throw Exception("Invalid data type in ColumnConstString: " + data_type->getName(), ErrorCodes::LOGICAL_ERROR);
}


template <> ColumnPtr ColumnConst<Array>::convertToFullColumn() const
{
	if (!data_type)
		throw Exception("No data type specified for ColumnConstArray", ErrorCodes::LOGICAL_ERROR);
	
	const DataTypeArray * type = dynamic_cast<const DataTypeArray *>(&*data_type);
	if (!type)
		throw Exception("Non-array data type specified for ColumnConstArray", ErrorCodes::LOGICAL_ERROR);
	
	size_t array_size = data.size();
	ColumnPtr nested_column = type->getNestedType()->createColumn();

	ColumnArray * res = new ColumnArray(nested_column);
	ColumnArray::Offsets_t & offsets = res->getOffsets();

	offsets.resize(s);
	for (size_t i = 0; i < s; ++i)
	{
		offsets[i] = (i + 1) * array_size;
		for (size_t j = 0; j < array_size; ++j)
			nested_column->insert(data[j]);
	}

	return res;
}


}

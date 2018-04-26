/**
 * \file  xml.c
 * \brief Holds xml reading and writing functions.
 */

#include "header.h"

/** \fn void read_int_static_array(char * buffer, int * j, int ** int_static_array)
 * \brief Reads integer static array.
 */
int read_int_static_array(char * buffer, int /*@unused@*/ buffer_size, int * j, int * int_static_array, int /*@unused@*/ size)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		if (arraycount < size) int_static_array[arraycount] = atoi(arraydata);
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}

	if (arraycount > size)
	{
				fprintf(stderr, "WARNING: %d 'int' values provided for static array of size %d. Surplus values ignored.\n",
				arraycount, size);
	}
	
	(*j)++;
	return 0;
}

/** \fn void read_float_static_array(char * buffer, int * (*j), int ** float_static_array)
 * \brief Reads float static array.
 */
int read_float_static_array(char * buffer, int /*@unused@*/ buffer_size, int * j, float * float_static_array, int /*@unused@*/ size)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		if (arraycount < size) float_static_array[arraycount] = (float)atof(arraydata);
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}
	
	if (arraycount > size)
	{
				fprintf(stderr, "WARNING: %d 'float' values provided for static array of size %d. Surplus values ignored.\n",
				arraycount, size);
	}
	
	(*j)++;
	return 0;
}

/** \fn void read_double_static_array(char * buffer, int * (*j), int ** double_static_array)
 * \brief Reads double static array.
 */
int read_double_static_array(char * buffer, int /*@unused@*/ buffer_size, int * j, double * double_static_array, int /*@unused@*/ size)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		if (arraycount < size) double_static_array[arraycount] = atof(arraydata);		
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}

	if (arraycount > size)
	{
		fprintf(stderr, "WARNING: %d 'double' values provided for static array of size %d. Surplus values ignored.\n",
				arraycount, size);
	}
	
	(*j)++;
	return 0;
}

/** \fn void read_char_static_array(char * buffer, int * (*j), int ** char_static_array)
 * \brief Reads char static array.
 */
int read_char_static_array(char * buffer, int /*@unused@*/ buffer_size, int * j, char * char_static_array, int size)
{
	int arraycount;
	
	while(buffer[(*j)] == ' ')
	{
		(*j)++;
	}
	
	for(arraycount = 0; arraycount < size; arraycount++)
	{
		char_static_array[arraycount] = buffer[(*j)];
		(*j)++;
	}

	//(*j)++;
	return 0;
}

/** \fn void read_int_dynamic_array(char * buffer, int * (*j), int ** int_dynamic_array)
 * \brief Reads integer dynamic array.
 */
int read_int_dynamic_array(char * buffer, int /*@unused@*/ buffer_size, int * j, int_array * int_dynamic_array)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		add_int(int_dynamic_array, atoi(arraydata));
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}

	(*j)++;
	return 0;
}

/** \fn void read_float_dynamic_array(char * buffer, int * (*j), int ** float_dynamic_array)
 * \brief Reads float dynamic array.
 */
int read_float_dynamic_array(char * buffer, int /*@unused@*/ buffer_size, int * j, float_array * float_dynamic_array)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		add_float(float_dynamic_array, (float)atof(arraydata));
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}

	(*j)++;
	return 0;
}

/** \fn void read_double_dynamic_array(char * buffer, int * (*j), int ** double_dynamic_array)
 * \brief Reads double dynamic array.
 */
int read_double_dynamic_array(char * buffer, int /*@unused@*/ buffer_size, int * j, double_array * double_dynamic_array)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		add_double(double_dynamic_array, atof(arraydata));
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}

	(*j)++;
	return 0;
}

/** \fn void read_char_dynamic_array(char * buffer, int * (*j), int ** char_dynamic_array)
 * \brief Reads char dynamic array.
 */
int read_char_dynamic_array(char * buffer, int /*@unused@*/ buffer_size, int * j, char_array * char_dynamic_array)
{
	if(*j > buffer_size) return -1;
	
	while(buffer[(*j)] == ' ')
	{
		(*j)++;
	}
	
	while(buffer[(*j)] != '\0' && buffer[(*j)] != ',' && buffer[(*j)] != '}')
	{
		add_char(char_dynamic_array, buffer[(*j)]);
		(*j)++;
	}
	
	return 0;
}


/** \fn void read_consumption_request(char * buffer, int * j, consumption_request * temp_datatype)
 * \brief Reads consumption_request datatype.
 */
int read_consumption_request(char * buffer, int /*@unused@*/ buffer_size, int * j, consumption_request * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).worker_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).worker_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).consumer_region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).consumer_region_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).firm_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).quantity = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quantity = atof(arraydata);
	(*j)++;

	return 0;
}

int read_consumption_request_dynamic_array(char * buffer, int buffer_size, int * j, consumption_request_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_consumption_request(temp_datatype_array, 0, 0, 0, 0.0);
			rc = read_consumption_request(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'consumption_request' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_consumption_request_static_array(char * buffer, int buffer_size, int * j, consumption_request * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_consumption_request(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'consumption_request' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_mall_info(char * buffer, int * j, mall_info * temp_datatype)
 * \brief Reads mall_info datatype.
 */
int read_mall_info(char * buffer, int /*@unused@*/ buffer_size, int * j, mall_info * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).mall_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mall_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).critical_stock = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).critical_stock = atof(arraydata);
	(*j)++;
	(*temp_datatype).current_stock = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).current_stock = atof(arraydata);
	(*j)++;

	return 0;
}

int read_mall_info_dynamic_array(char * buffer, int buffer_size, int * j, mall_info_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_mall_info(temp_datatype_array, 0, 0.0, 0.0);
			rc = read_mall_info(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'mall_info' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_mall_info_static_array(char * buffer, int buffer_size, int * j, mall_info * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_mall_info(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'mall_info' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_mall_quality_price_info(char * buffer, int * j, mall_quality_price_info * temp_datatype)
 * \brief Reads mall_quality_price_info datatype.
 */
int read_mall_quality_price_info(char * buffer, int /*@unused@*/ buffer_size, int * j, mall_quality_price_info * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).mall_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mall_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).firm_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).mall_region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mall_region_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).quality = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quality = atof(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;
	(*temp_datatype).available = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).available = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_mall_quality_price_info_dynamic_array(char * buffer, int buffer_size, int * j, mall_quality_price_info_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_mall_quality_price_info(temp_datatype_array, 0, 0, 0, 0.0, 0.0, 0);
			rc = read_mall_quality_price_info(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'mall_quality_price_info' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_mall_quality_price_info_static_array(char * buffer, int buffer_size, int * j, mall_quality_price_info * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_mall_quality_price_info(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'mall_quality_price_info' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_mall_stock(char * buffer, int * j, mall_stock * temp_datatype)
 * \brief Reads mall_stock datatype.
 */
int read_mall_stock(char * buffer, int /*@unused@*/ buffer_size, int * j, mall_stock * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).firm_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).region_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).stock = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).stock = atof(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;
	(*temp_datatype).quality = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quality = atof(arraydata);
	(*j)++;
	(*temp_datatype).previous_price = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).previous_price = atof(arraydata);
	(*j)++;

	return 0;
}

int read_mall_stock_dynamic_array(char * buffer, int buffer_size, int * j, mall_stock_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_mall_stock(temp_datatype_array, 0, 0, 0.0, 0.0, 0.0, 0.0);
			rc = read_mall_stock(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'mall_stock' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_mall_stock_static_array(char * buffer, int buffer_size, int * j, mall_stock * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_mall_stock(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'mall_stock' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_delivery_volume_per_mall(char * buffer, int * j, delivery_volume_per_mall * temp_datatype)
 * \brief Reads delivery_volume_per_mall datatype.
 */
int read_delivery_volume_per_mall(char * buffer, int /*@unused@*/ buffer_size, int * j, delivery_volume_per_mall * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).mall_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mall_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).quantity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quantity = atof(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;
	(*temp_datatype).quality = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quality = atof(arraydata);
	(*j)++;

	return 0;
}

int read_delivery_volume_per_mall_dynamic_array(char * buffer, int buffer_size, int * j, delivery_volume_per_mall_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_delivery_volume_per_mall(temp_datatype_array, 0, 0.0, 0.0, 0.0);
			rc = read_delivery_volume_per_mall(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'delivery_volume_per_mall' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_delivery_volume_per_mall_static_array(char * buffer, int buffer_size, int * j, delivery_volume_per_mall * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_delivery_volume_per_mall(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'delivery_volume_per_mall' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_logit_firm_id(char * buffer, int * j, logit_firm_id * temp_datatype)
 * \brief Reads logit_firm_id datatype.
 */
int read_logit_firm_id(char * buffer, int /*@unused@*/ buffer_size, int * j, logit_firm_id * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).logit = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).logit = atof(arraydata);
	(*j)++;
	(*temp_datatype).firm_id = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_id = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_logit_firm_id_dynamic_array(char * buffer, int buffer_size, int * j, logit_firm_id_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_logit_firm_id(temp_datatype_array, 0.0, 0);
			rc = read_logit_firm_id(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'logit_firm_id' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_logit_firm_id_static_array(char * buffer, int buffer_size, int * j, logit_firm_id * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_logit_firm_id(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'logit_firm_id' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_sales_in_mall(char * buffer, int * j, sales_in_mall * temp_datatype)
 * \brief Reads sales_in_mall datatype.
 */
int read_sales_in_mall(char * buffer, int /*@unused@*/ buffer_size, int * j, sales_in_mall * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).firm_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).sales = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sales = atof(arraydata);
	(*j)++;

	return 0;
}

int read_sales_in_mall_dynamic_array(char * buffer, int buffer_size, int * j, sales_in_mall_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_sales_in_mall(temp_datatype_array, 0, 0.0);
			rc = read_sales_in_mall(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'sales_in_mall' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_sales_in_mall_static_array(char * buffer, int buffer_size, int * j, sales_in_mall * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_sales_in_mall(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'sales_in_mall' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_ordered_quantity(char * buffer, int * j, ordered_quantity * temp_datatype)
 * \brief Reads ordered_quantity datatype.
 */
int read_ordered_quantity(char * buffer, int /*@unused@*/ buffer_size, int * j, ordered_quantity * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).firm_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).quantity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quantity = atof(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;
	(*temp_datatype).quality = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quality = atof(arraydata);
	(*j)++;

	return 0;
}

int read_ordered_quantity_dynamic_array(char * buffer, int buffer_size, int * j, ordered_quantity_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_ordered_quantity(temp_datatype_array, 0, 0.0, 0.0, 0.0);
			rc = read_ordered_quantity(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'ordered_quantity' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_ordered_quantity_static_array(char * buffer, int buffer_size, int * j, ordered_quantity * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_ordered_quantity(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'ordered_quantity' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_received_quantities(char * buffer, int * j, received_quantities * temp_datatype)
 * \brief Reads received_quantities datatype.
 */
int read_received_quantities(char * buffer, int /*@unused@*/ buffer_size, int * j, received_quantities * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).firm_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).quantity = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quantity = atof(arraydata);
	(*j)++;

	return 0;
}

int read_received_quantities_dynamic_array(char * buffer, int buffer_size, int * j, received_quantities_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_received_quantities(temp_datatype_array, 0, 0.0);
			rc = read_received_quantities(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'received_quantities' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_received_quantities_static_array(char * buffer, int buffer_size, int * j, received_quantities * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_received_quantities(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'received_quantities' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_sold_quantities_per_mall(char * buffer, int * j, sold_quantities_per_mall * temp_datatype)
 * \brief Reads sold_quantities_per_mall datatype.
 */
int read_sold_quantities_per_mall(char * buffer, int /*@unused@*/ buffer_size, int * j, sold_quantities_per_mall * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).mall_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mall_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).sold_quantity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sold_quantity = atof(arraydata);
	(*j)++;
	(*temp_datatype).stock_empty = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).stock_empty = atoi(arraydata);
	(*j)++;
	(*temp_datatype).estimated_demand = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).estimated_demand = atof(arraydata);
	(*j)++;

	return 0;
}

int read_sold_quantities_per_mall_dynamic_array(char * buffer, int buffer_size, int * j, sold_quantities_per_mall_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_sold_quantities_per_mall(temp_datatype_array, 0, 0.0, 0, 0.0);
			rc = read_sold_quantities_per_mall(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'sold_quantities_per_mall' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_sold_quantities_per_mall_static_array(char * buffer, int buffer_size, int * j, sold_quantities_per_mall * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_sold_quantities_per_mall(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'sold_quantities_per_mall' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_data_type_sales(char * buffer, int * j, data_type_sales * temp_datatype)
 * \brief Reads data_type_sales datatype.
 */
int read_data_type_sales(char * buffer, int /*@unused@*/ buffer_size, int * j, data_type_sales * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).period = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).period = atoi(arraydata);
	(*j)++;
	(*temp_datatype).sales = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sales = atof(arraydata);
	(*j)++;

	return 0;
}

int read_data_type_sales_dynamic_array(char * buffer, int buffer_size, int * j, data_type_sales_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_data_type_sales(temp_datatype_array, 0, 0.0);
			rc = read_data_type_sales(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'data_type_sales' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_data_type_sales_static_array(char * buffer, int buffer_size, int * j, data_type_sales * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_data_type_sales(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'data_type_sales' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_sales_statistics(char * buffer, int * j, sales_statistics * temp_datatype)
 * \brief Reads sales_statistics datatype.
 */
int read_sales_statistics(char * buffer, int /*@unused@*/ buffer_size, int * j, sales_statistics * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).mall_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mall_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).region_id = atoi(arraydata);
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_data_type_sales_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).sales);
	if(rc != 0) return -1;
	
	(*j)++;

	return 0;
}

int read_sales_statistics_dynamic_array(char * buffer, int buffer_size, int * j, sales_statistics_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	data_type_sales_array sales;
# ifndef S_SPLINT_S
	init_data_type_sales_array(&sales);
# endif

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_sales_statistics(temp_datatype_array, 0, 0, &sales);
			rc = read_sales_statistics(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'sales_statistics' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_data_type_sales_array(&sales);
	
	
	return 0;
}

int read_sales_statistics_static_array(char * buffer, int buffer_size, int * j, sales_statistics * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_sales_statistics(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'sales_statistics' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_adt_technology_vintages(char * buffer, int * j, adt_technology_vintages * temp_datatype)
 * \brief Reads adt_technology_vintages datatype.
 */
int read_adt_technology_vintages(char * buffer, int /*@unused@*/ buffer_size, int * j, adt_technology_vintages * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).productivity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).productivity = atof(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;
	(*temp_datatype).sum_effective_productivities = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sum_effective_productivities = atof(arraydata);
	(*j)++;

	return 0;
}

int read_adt_technology_vintages_dynamic_array(char * buffer, int buffer_size, int * j, adt_technology_vintages_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_adt_technology_vintages(temp_datatype_array, 0.0, 0.0, 0.0);
			rc = read_adt_technology_vintages(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'adt_technology_vintages' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_adt_technology_vintages_static_array(char * buffer, int buffer_size, int * j, adt_technology_vintages * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_adt_technology_vintages(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'adt_technology_vintages' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_adt_capital_stock_vintages(char * buffer, int * j, adt_capital_stock_vintages * temp_datatype)
 * \brief Reads adt_capital_stock_vintages datatype.
 */
int read_adt_capital_stock_vintages(char * buffer, int /*@unused@*/ buffer_size, int * j, adt_capital_stock_vintages * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).amount = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).amount = atof(arraydata);
	(*j)++;
	(*temp_datatype).productivity = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).productivity = atof(arraydata);
	(*j)++;

	return 0;
}

int read_adt_capital_stock_vintages_dynamic_array(char * buffer, int buffer_size, int * j, adt_capital_stock_vintages_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_adt_capital_stock_vintages(temp_datatype_array, 0.0, 0.0);
			rc = read_adt_capital_stock_vintages(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'adt_capital_stock_vintages' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_adt_capital_stock_vintages_static_array(char * buffer, int buffer_size, int * j, adt_capital_stock_vintages * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_adt_capital_stock_vintages(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'adt_capital_stock_vintages' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_financing_capital(char * buffer, int * j, financing_capital * temp_datatype)
 * \brief Reads financing_capital datatype.
 */
int read_financing_capital(char * buffer, int /*@unused@*/ buffer_size, int * j, financing_capital * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).financing_per_month = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).financing_per_month = atof(arraydata);
	(*j)++;
	(*temp_datatype).nr_periods_before_repayment = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).nr_periods_before_repayment = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_financing_capital_dynamic_array(char * buffer, int buffer_size, int * j, financing_capital_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_financing_capital(temp_datatype_array, 0.0, 0);
			rc = read_financing_capital(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'financing_capital' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_financing_capital_static_array(char * buffer, int buffer_size, int * j, financing_capital * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_financing_capital(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'financing_capital' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_temporary_sales_statistics(char * buffer, int * j, temporary_sales_statistics * temp_datatype)
 * \brief Reads temporary_sales_statistics datatype.
 */
int read_temporary_sales_statistics(char * buffer, int /*@unused@*/ buffer_size, int * j, temporary_sales_statistics * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).mall_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mall_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).period = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).period = atoi(arraydata);
	(*j)++;
	(*temp_datatype).sales = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sales = atof(arraydata);
	(*j)++;

	return 0;
}

int read_temporary_sales_statistics_dynamic_array(char * buffer, int buffer_size, int * j, temporary_sales_statistics_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_temporary_sales_statistics(temp_datatype_array, 0, 0, 0.0);
			rc = read_temporary_sales_statistics(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'temporary_sales_statistics' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_temporary_sales_statistics_static_array(char * buffer, int buffer_size, int * j, temporary_sales_statistics * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_temporary_sales_statistics(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'temporary_sales_statistics' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_tenant_adt(char * buffer, int * j, tenant_adt * temp_datatype)
 * \brief Reads tenant_adt datatype.
 */
int read_tenant_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, tenant_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).monthly_rent = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).monthly_rent = atof(arraydata);
	(*j)++;

	return 0;
}

int read_tenant_adt_dynamic_array(char * buffer, int buffer_size, int * j, tenant_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_tenant_adt(temp_datatype_array, 0, 0.0);
			rc = read_tenant_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'tenant_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_tenant_adt_static_array(char * buffer, int buffer_size, int * j, tenant_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_tenant_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'tenant_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_house_adt(char * buffer, int * j, house_adt * temp_datatype)
 * \brief Reads house_adt datatype.
 */
int read_house_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, house_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).object_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).object_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).seller_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).seller_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).buyer_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).buyer_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).value = atof(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;

	return 0;
}

int read_house_adt_dynamic_array(char * buffer, int buffer_size, int * j, house_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_house_adt(temp_datatype_array, 0, 0, 0, 0.0, 0.0);
			rc = read_house_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'house_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_house_adt_static_array(char * buffer, int buffer_size, int * j, house_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_house_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'house_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_foreclosure_adt(char * buffer, int * j, foreclosure_adt * temp_datatype)
 * \brief Reads foreclosure_adt datatype.
 */
int read_foreclosure_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, foreclosure_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).object_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).object_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).former_owner_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).former_owner_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).bank_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).bank_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).value = atof(arraydata);
	(*j)++;
	(*temp_datatype).claim = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).claim = atof(arraydata);
	(*j)++;

	return 0;
}

int read_foreclosure_adt_dynamic_array(char * buffer, int buffer_size, int * j, foreclosure_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_foreclosure_adt(temp_datatype_array, 0, 0, 0, 0.0, 0.0);
			rc = read_foreclosure_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'foreclosure_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_foreclosure_adt_static_array(char * buffer, int buffer_size, int * j, foreclosure_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_foreclosure_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'foreclosure_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_rental_adt(char * buffer, int * j, rental_adt * temp_datatype)
 * \brief Reads rental_adt datatype.
 */
int read_rental_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, rental_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).object_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).object_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).tenant_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).tenant_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).landlord_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).landlord_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).monthly_rent = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).monthly_rent = atof(arraydata);
	(*j)++;
	(*temp_datatype).sold = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sold = atoi(arraydata);
	(*j)++;
	(*temp_datatype).value = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).value = atof(arraydata);
	(*j)++;

	return 0;
}

int read_rental_adt_dynamic_array(char * buffer, int buffer_size, int * j, rental_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_rental_adt(temp_datatype_array, 0, 0, 0, 0.0, 0, 0.0);
			rc = read_rental_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'rental_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_rental_adt_static_array(char * buffer, int buffer_size, int * j, rental_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_rental_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'rental_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_mortgage_contract_adt(char * buffer, int * j, mortgage_contract_adt * temp_datatype)
 * \brief Reads mortgage_contract_adt datatype.
 */
int read_mortgage_contract_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, mortgage_contract_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).household_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).household_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).bank_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).bank_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).initial_duration = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).initial_duration = atoi(arraydata);
	(*j)++;
	(*temp_datatype).initial_principal = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).initial_principal = atof(arraydata);
	(*j)++;
	(*temp_datatype).initial_loan_to_value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).initial_loan_to_value = atof(arraydata);
	(*j)++;
	(*temp_datatype).initial_total_interest = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).initial_total_interest = atof(arraydata);
	(*j)++;
	(*temp_datatype).initial_risk_of_default = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).initial_risk_of_default = atof(arraydata);
	(*j)++;
	(*temp_datatype).interest_rate_annual = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).interest_rate_annual = atof(arraydata);
	(*j)++;
	(*temp_datatype).current_duration = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).current_duration = atoi(arraydata);
	(*j)++;
	(*temp_datatype).outstanding_principal = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).outstanding_principal = atof(arraydata);
	(*j)++;
	(*temp_datatype).outstanding_interest = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).outstanding_interest = atof(arraydata);
	(*j)++;
	(*temp_datatype).monthly_total_repayment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).monthly_total_repayment = atof(arraydata);
	(*j)++;
	(*temp_datatype).monthly_principal = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).monthly_principal = atof(arraydata);
	(*j)++;
	(*temp_datatype).monthly_interest = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).monthly_interest = atof(arraydata);
	(*j)++;
	(*temp_datatype).current_risk_of_default = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).current_risk_of_default = atof(arraydata);
	(*j)++;
	(*temp_datatype).status = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).status = atoi(arraydata);
	(*j)++;
	(*temp_datatype).arrears_counter = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).arrears_counter = atoi(arraydata);
	(*j)++;
	(*temp_datatype).npl_counter = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).npl_counter = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_mortgage_contract_adt_dynamic_array(char * buffer, int buffer_size, int * j, mortgage_contract_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_mortgage_contract_adt(temp_datatype_array, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0);
			rc = read_mortgage_contract_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'mortgage_contract_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_mortgage_contract_adt_static_array(char * buffer, int buffer_size, int * j, mortgage_contract_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_mortgage_contract_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'mortgage_contract_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_mortgage_application_adt(char * buffer, int * j, mortgage_application_adt * temp_datatype)
 * \brief Reads mortgage_application_adt datatype.
 */
int read_mortgage_application_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, mortgage_application_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).household_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).household_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).annuity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).annuity = atof(arraydata);
	(*j)++;
	(*temp_datatype).dstic = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).dstic = atof(arraydata);
	(*j)++;
	(*temp_datatype).sampled_loan_to_value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_loan_to_value = atof(arraydata);
	(*j)++;
	(*temp_datatype).sampled_duration = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_duration = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_mortgage_application_adt_dynamic_array(char * buffer, int buffer_size, int * j, mortgage_application_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_mortgage_application_adt(temp_datatype_array, 0, 0.0, 0.0, 0.0, 0);
			rc = read_mortgage_application_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'mortgage_application_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_mortgage_application_adt_static_array(char * buffer, int buffer_size, int * j, mortgage_application_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_mortgage_application_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'mortgage_application_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_mortgage_sample_adt(char * buffer, int * j, mortgage_sample_adt * temp_datatype)
 * \brief Reads mortgage_sample_adt datatype.
 */
int read_mortgage_sample_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, mortgage_sample_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).sampled_initial_principal = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_initial_principal = atof(arraydata);
	(*j)++;
	(*temp_datatype).sampled_initial_duration = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_initial_duration = atoi(arraydata);
	(*j)++;
	(*temp_datatype).sampled_outstanding_principal = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_outstanding_principal = atof(arraydata);
	(*j)++;
	(*temp_datatype).sampled_interest_rate_annual = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_interest_rate_annual = atof(arraydata);
	(*j)++;
	(*temp_datatype).sampled_monthly_total_repayment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_monthly_total_repayment = atof(arraydata);
	(*j)++;
	(*temp_datatype).sampled_percent_ownership = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_percent_ownership = atoi(arraydata);
	(*j)++;
	(*temp_datatype).sampled_value_at_acquisition = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_value_at_acquisition = atof(arraydata);
	(*j)++;
	(*temp_datatype).sampled_initial_ltv = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_initial_ltv = atof(arraydata);
	(*j)++;

	return 0;
}

int read_mortgage_sample_adt_dynamic_array(char * buffer, int buffer_size, int * j, mortgage_sample_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_mortgage_sample_adt(temp_datatype_array, 0.0, 0, 0.0, 0.0, 0.0, 0, 0.0, 0.0);
			rc = read_mortgage_sample_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'mortgage_sample_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_mortgage_sample_adt_static_array(char * buffer, int buffer_size, int * j, mortgage_sample_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_mortgage_sample_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'mortgage_sample_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_sample_adt(char * buffer, int * j, sample_adt * temp_datatype)
 * \brief Reads sample_adt datatype.
 */
int read_sample_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, sample_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).sampled_total_monthly_income = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_total_monthly_income = atof(arraydata);
	(*j)++;
	(*temp_datatype).sampled_monthly_rent = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sampled_monthly_rent = atof(arraydata);
	(*j)++;

	return 0;
}

int read_sample_adt_dynamic_array(char * buffer, int buffer_size, int * j, sample_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_sample_adt(temp_datatype_array, 0.0, 0.0);
			rc = read_sample_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'sample_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_sample_adt_static_array(char * buffer, int buffer_size, int * j, sample_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_sample_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'sample_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_debt_item(char * buffer, int * j, debt_item * temp_datatype)
 * \brief Reads debt_item datatype.
 */
int read_debt_item(char * buffer, int /*@unused@*/ buffer_size, int * j, debt_item * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).bank_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).bank_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).loan_value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).loan_value = atof(arraydata);
	(*j)++;
	(*temp_datatype).interest_rate = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).interest_rate = atof(arraydata);
	(*j)++;
	(*temp_datatype).installment_amount = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).installment_amount = atof(arraydata);
	(*j)++;
	(*temp_datatype).exposure_per_installment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).exposure_per_installment = atof(arraydata);
	(*j)++;
	(*temp_datatype).residual_exposure = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).residual_exposure = atof(arraydata);
	(*j)++;
	(*temp_datatype).bad_debt = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).bad_debt = atof(arraydata);
	(*j)++;
	(*temp_datatype).nr_periods_before_repayment = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).nr_periods_before_repayment = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_debt_item_dynamic_array(char * buffer, int buffer_size, int * j, debt_item_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_debt_item(temp_datatype_array, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0);
			rc = read_debt_item(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'debt_item' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_debt_item_static_array(char * buffer, int buffer_size, int * j, debt_item * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_debt_item(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'debt_item' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_account_item(char * buffer, int * j, account_item * temp_datatype)
 * \brief Reads account_item datatype.
 */
int read_account_item(char * buffer, int /*@unused@*/ buffer_size, int * j, account_item * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).payment_account = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account = atof(arraydata);
	(*j)++;

	return 0;
}

int read_account_item_dynamic_array(char * buffer, int buffer_size, int * j, account_item_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_account_item(temp_datatype_array, 0, 0.0);
			rc = read_account_item(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'account_item' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_account_item_static_array(char * buffer, int buffer_size, int * j, account_item * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_account_item(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'account_item' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_financial_data_adt(char * buffer, int * j, financial_data_adt * temp_datatype)
 * \brief Reads financial_data_adt datatype.
 */
int read_financial_data_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, financial_data_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).equity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).equity = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_assets = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_assets = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_debt = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_debt = atof(arraydata);
	(*j)++;
	(*temp_datatype).equity_asset_ratio = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).equity_asset_ratio = atof(arraydata);
	(*j)++;
	(*temp_datatype).debt_equity_ratio = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).debt_equity_ratio = atof(arraydata);
	(*j)++;

	return 0;
}

int read_financial_data_adt_dynamic_array(char * buffer, int buffer_size, int * j, financial_data_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_financial_data_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_financial_data_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'financial_data_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_financial_data_adt_static_array(char * buffer, int buffer_size, int * j, financial_data_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_financial_data_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'financial_data_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_node_adt(char * buffer, int * j, node_adt * temp_datatype)
 * \brief Reads node_adt datatype.
 */
int read_node_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, node_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).id = atoi(arraydata);
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_financial_data_adt(buffer, buffer_size, j, &(*temp_datatype).financial_data);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_debt_item_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).loan_portfolio);
	if(rc != 0) return -1;
	
	(*j)++;

	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		while(buffer[*j] != '{') (*j)++;
		
		rc = read_int_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).friend_id_list);
		if(rc != 0) { printf("Error: reading variable 'friend_id_list' of type 'int_array'\n"); return -1; }
	}
	
	(*j)++;
	(*temp_datatype).type_of_node = ' ';
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).type_of_node = (arraydata[array_k-1]);
	(*j)++;

	return 0;
}

int read_node_adt_dynamic_array(char * buffer, int buffer_size, int * j, node_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	financial_data_adt financial_data;
# ifndef S_SPLINT_S
	init_financial_data_adt(&financial_data);
# endif
	
	
	debt_item_array loan_portfolio;
# ifndef S_SPLINT_S
	init_debt_item_array(&loan_portfolio);
# endif
	
	int_array friend_id_list;
# ifndef S_SPLINT_S
	init_int_array(&friend_id_list);
# endif
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_node_adt(temp_datatype_array, 0, &financial_data, &loan_portfolio, &friend_id_list, ' ');
			rc = read_node_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'node_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_debt_item_array(&loan_portfolio);
	free_int_array(&friend_id_list);
	
	
	return 0;
}

int read_node_adt_static_array(char * buffer, int buffer_size, int * j, node_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_node_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'node_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_order(char * buffer, int * j, order * temp_datatype)
 * \brief Reads order datatype.
 */
int read_order(char * buffer, int /*@unused@*/ buffer_size, int * j, order * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).trader_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).trader_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).value = atof(arraydata);
	(*j)++;
	(*temp_datatype).quantity = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quantity = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_order_dynamic_array(char * buffer, int buffer_size, int * j, order_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_order(temp_datatype_array, 0, 0.0, 0);
			rc = read_order(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'order' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_order_static_array(char * buffer, int buffer_size, int * j, order * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_order(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'order' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_index_adt(char * buffer, int * j, index_adt * temp_datatype)
 * \brief Reads index_adt datatype.
 */
int read_index_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, index_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;
	(*temp_datatype).weight = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).weight = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_dividend = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_dividend = atof(arraydata);
	(*j)++;
	(*temp_datatype).dividend_per_share = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).dividend_per_share = atof(arraydata);
	(*j)++;
	(*temp_datatype).nr_shares = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).nr_shares = atoi(arraydata);
	(*j)++;
	(*temp_datatype).moving_avg_price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).moving_avg_price = atof(arraydata);
	(*j)++;

	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		while(buffer[*j] != '{') (*j)++;
		
		rc = read_double_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).price_history);
		if(rc != 0) { printf("Error: reading variable 'price_history' of type 'double_array'\n"); return -1; }
	}
	
	(*j)++;

	return 0;
}

int read_index_adt_dynamic_array(char * buffer, int buffer_size, int * j, index_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	double_array price_history;
# ifndef S_SPLINT_S
	init_double_array(&price_history);
# endif

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_index_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0, 0.0, &price_history);
			rc = read_index_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'index_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_double_array(&price_history);
	
	
	return 0;
}

int read_index_adt_static_array(char * buffer, int buffer_size, int * j, index_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_index_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'index_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_index_portfolio(char * buffer, int * j, index_portfolio * temp_datatype)
 * \brief Reads index_portfolio datatype.
 */
int read_index_portfolio(char * buffer, int /*@unused@*/ buffer_size, int * j, index_portfolio * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).lastprice = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).lastprice = atof(arraydata);
	(*j)++;
	(*temp_datatype).units = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).units = atoi(arraydata);
	(*j)++;
	(*temp_datatype).moving_avg_price = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).moving_avg_price = atof(arraydata);
	(*j)++;

	return 0;
}

int read_index_portfolio_dynamic_array(char * buffer, int buffer_size, int * j, index_portfolio_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_index_portfolio(temp_datatype_array, 0.0, 0, 0.0);
			rc = read_index_portfolio(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'index_portfolio' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_index_portfolio_static_array(char * buffer, int buffer_size, int * j, index_portfolio * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_index_portfolio(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'index_portfolio' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_Belief(char * buffer, int * j, Belief * temp_datatype)
 * \brief Reads Belief datatype.
 */
int read_Belief(char * buffer, int /*@unused@*/ buffer_size, int * j, Belief * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).expected_dividend = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).expected_dividend = atof(arraydata);
	(*j)++;
	(*temp_datatype).expected_price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).expected_price = atof(arraydata);
	(*j)++;
	(*temp_datatype).expected_return = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).expected_return = atof(arraydata);
	(*j)++;
	(*temp_datatype).expected_volatility = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).expected_volatility = atof(arraydata);
	(*j)++;
	(*temp_datatype).last_price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).last_price = atof(arraydata);
	(*j)++;
	(*temp_datatype).fraction_to_invest = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).fraction_to_invest = atof(arraydata);
	(*j)++;

	return 0;
}

int read_Belief_dynamic_array(char * buffer, int buffer_size, int * j, Belief_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_Belief(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_Belief(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'Belief' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_Belief_static_array(char * buffer, int buffer_size, int * j, Belief * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_Belief(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'Belief' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_capital_good_request(char * buffer, int * j, capital_good_request * temp_datatype)
 * \brief Reads capital_good_request datatype.
 */
int read_capital_good_request(char * buffer, int /*@unused@*/ buffer_size, int * j, capital_good_request * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).firm_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).capital_good_order = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).capital_good_order = atof(arraydata);
	(*j)++;
	(*temp_datatype).vintage = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).vintage = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_capital_good_request_dynamic_array(char * buffer, int buffer_size, int * j, capital_good_request_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_capital_good_request(temp_datatype_array, 0, 0.0, 0);
			rc = read_capital_good_request(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'capital_good_request' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_capital_good_request_static_array(char * buffer, int buffer_size, int * j, capital_good_request * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_capital_good_request(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'capital_good_request' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_vintage(char * buffer, int * j, vintage * temp_datatype)
 * \brief Reads vintage datatype.
 */
int read_vintage(char * buffer, int /*@unused@*/ buffer_size, int * j, vintage * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).productivity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).productivity = atof(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;
	(*temp_datatype).discounted_productivity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).discounted_productivity = atof(arraydata);
	(*j)++;
	(*temp_datatype).sales = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sales = atof(arraydata);
	(*j)++;

	return 0;
}

int read_vintage_dynamic_array(char * buffer, int buffer_size, int * j, vintage_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_vintage(temp_datatype_array, 0.0, 0.0, 0.0, 0.0);
			rc = read_vintage(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'vintage' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_vintage_static_array(char * buffer, int buffer_size, int * j, vintage * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_vintage(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'vintage' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_adt_sales_per_vintage(char * buffer, int * j, adt_sales_per_vintage * temp_datatype)
 * \brief Reads adt_sales_per_vintage datatype.
 */
int read_adt_sales_per_vintage(char * buffer, int /*@unused@*/ buffer_size, int * j, adt_sales_per_vintage * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).productivity_of_vintage = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).productivity_of_vintage = atof(arraydata);
	(*j)++;
	(*temp_datatype).sales = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sales = atof(arraydata);
	(*j)++;
	(*temp_datatype).revenue = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).revenue = atof(arraydata);
	(*j)++;

	return 0;
}

int read_adt_sales_per_vintage_dynamic_array(char * buffer, int buffer_size, int * j, adt_sales_per_vintage_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_adt_sales_per_vintage(temp_datatype_array, 0.0, 0.0, 0.0);
			rc = read_adt_sales_per_vintage(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'adt_sales_per_vintage' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_adt_sales_per_vintage_static_array(char * buffer, int buffer_size, int * j, adt_sales_per_vintage * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_adt_sales_per_vintage(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'adt_sales_per_vintage' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_employee(char * buffer, int * j, employee * temp_datatype)
 * \brief Reads employee datatype.
 */
int read_employee(char * buffer, int /*@unused@*/ buffer_size, int * j, employee * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).region_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).wage = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).wage = atof(arraydata);
	(*j)++;
	(*temp_datatype).general_skill = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).general_skill = atoi(arraydata);
	(*j)++;
	(*temp_datatype).specific_skill = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).specific_skill = atof(arraydata);
	(*j)++;
	(*temp_datatype).specific_skill_before_learning = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).specific_skill_before_learning = atof(arraydata);
	(*j)++;

	return 0;
}

int read_employee_dynamic_array(char * buffer, int buffer_size, int * j, employee_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_employee(temp_datatype_array, 0, 0, 0.0, 0, 0.0, 0.0);
			rc = read_employee(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'employee' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_employee_static_array(char * buffer, int buffer_size, int * j, employee * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_employee(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'employee' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_vacancy(char * buffer, int * j, vacancy * temp_datatype)
 * \brief Reads vacancy datatype.
 */
int read_vacancy(char * buffer, int /*@unused@*/ buffer_size, int * j, vacancy * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).firm_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).region_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).wage_offer = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).wage_offer = atof(arraydata);
	(*j)++;
	(*temp_datatype).job_type = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).job_type = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_vacancy_dynamic_array(char * buffer, int buffer_size, int * j, vacancy_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_vacancy(temp_datatype_array, 0, 0, 0.0, 0);
			rc = read_vacancy(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'vacancy' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_vacancy_static_array(char * buffer, int buffer_size, int * j, vacancy * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_vacancy(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'vacancy' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_job_application(char * buffer, int * j, job_application * temp_datatype)
 * \brief Reads job_application datatype.
 */
int read_job_application(char * buffer, int /*@unused@*/ buffer_size, int * j, job_application * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).worker_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).worker_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).region_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).general_skill = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).general_skill = atoi(arraydata);
	(*j)++;
	(*temp_datatype).specific_skill = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).specific_skill = atof(arraydata);
	(*j)++;

	return 0;
}

int read_job_application_dynamic_array(char * buffer, int buffer_size, int * j, job_application_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_job_application(temp_datatype_array, 0, 0, 0, 0.0);
			rc = read_job_application(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'job_application' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_job_application_static_array(char * buffer, int buffer_size, int * j, job_application * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_job_application(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'job_application' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_job_offer(char * buffer, int * j, job_offer * temp_datatype)
 * \brief Reads job_offer datatype.
 */
int read_job_offer(char * buffer, int /*@unused@*/ buffer_size, int * j, job_offer * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).firm_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).region_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).wage_offer = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).wage_offer = atof(arraydata);
	(*j)++;
	(*temp_datatype).job_type = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).job_type = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_job_offer_dynamic_array(char * buffer, int buffer_size, int * j, job_offer_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_job_offer(temp_datatype_array, 0, 0, 0.0, 0);
			rc = read_job_offer(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'job_offer' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_job_offer_static_array(char * buffer, int buffer_size, int * j, job_offer * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_job_offer(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'job_offer' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_logit(char * buffer, int * j, logit * temp_datatype)
 * \brief Reads logit datatype.
 */
int read_logit(char * buffer, int /*@unused@*/ buffer_size, int * j, logit * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).logit_value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).logit_value = atof(arraydata);
	(*j)++;
	(*temp_datatype).worker_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).worker_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).general_skill = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).general_skill = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_logit_dynamic_array(char * buffer, int buffer_size, int * j, logit_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_logit(temp_datatype_array, 0.0, 0, 0);
			rc = read_logit(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'logit' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_logit_static_array(char * buffer, int buffer_size, int * j, logit * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_logit(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'logit' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_adt_list_adaptation_speed(char * buffer, int * j, adt_list_adaptation_speed * temp_datatype)
 * \brief Reads adt_list_adaptation_speed datatype.
 */
int read_adt_list_adaptation_speed(char * buffer, int /*@unused@*/ buffer_size, int * j, adt_list_adaptation_speed * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).general_skill_level = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).general_skill_level = atoi(arraydata);
	(*j)++;
	(*temp_datatype).adaptation_speed = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).adaptation_speed = atof(arraydata);
	(*j)++;

	return 0;
}

int read_adt_list_adaptation_speed_dynamic_array(char * buffer, int buffer_size, int * j, adt_list_adaptation_speed_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_adt_list_adaptation_speed(temp_datatype_array, 0, 0.0);
			rc = read_adt_list_adaptation_speed(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'adt_list_adaptation_speed' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_adt_list_adaptation_speed_static_array(char * buffer, int buffer_size, int * j, adt_list_adaptation_speed * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_adt_list_adaptation_speed(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'adt_list_adaptation_speed' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_adt_skill_distribution(char * buffer, int * j, adt_skill_distribution * temp_datatype)
 * \brief Reads adt_skill_distribution datatype.
 */
int read_adt_skill_distribution(char * buffer, int /*@unused@*/ buffer_size, int * j, adt_skill_distribution * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).general_skill_group = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).general_skill_group = atoi(arraydata);
	(*j)++;
	(*temp_datatype).percentage = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).percentage = atof(arraydata);
	(*j)++;

	return 0;
}

int read_adt_skill_distribution_dynamic_array(char * buffer, int buffer_size, int * j, adt_skill_distribution_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_adt_skill_distribution(temp_datatype_array, 0, 0.0);
			rc = read_adt_skill_distribution(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'adt_skill_distribution' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_adt_skill_distribution_static_array(char * buffer, int buffer_size, int * j, adt_skill_distribution * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_adt_skill_distribution(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'adt_skill_distribution' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_adt_actual_skill_distribution_with_ids(char * buffer, int * j, adt_actual_skill_distribution_with_ids * temp_datatype)
 * \brief Reads adt_actual_skill_distribution_with_ids datatype.
 */
int read_adt_actual_skill_distribution_with_ids(char * buffer, int /*@unused@*/ buffer_size, int * j, adt_actual_skill_distribution_with_ids * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).general_skill_group = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).general_skill_group = atoi(arraydata);
	(*j)++;

	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		while(buffer[*j] != '{') (*j)++;
		
		rc = read_int_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).id_list);
		if(rc != 0) { printf("Error: reading variable 'id_list' of type 'int_array'\n"); return -1; }
	}
	
	(*j)++;

	return 0;
}

int read_adt_actual_skill_distribution_with_ids_dynamic_array(char * buffer, int buffer_size, int * j, adt_actual_skill_distribution_with_ids_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	int_array id_list;
# ifndef S_SPLINT_S
	init_int_array(&id_list);
# endif

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_adt_actual_skill_distribution_with_ids(temp_datatype_array, 0, &id_list);
			rc = read_adt_actual_skill_distribution_with_ids(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'adt_actual_skill_distribution_with_ids' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_int_array(&id_list);
	
	
	return 0;
}

int read_adt_actual_skill_distribution_with_ids_static_array(char * buffer, int buffer_size, int * j, adt_actual_skill_distribution_with_ids * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_adt_actual_skill_distribution_with_ids(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'adt_actual_skill_distribution_with_ids' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_price_index_adt(char * buffer, int * j, price_index_adt * temp_datatype)
 * \brief Reads price_index_adt datatype.
 */
int read_price_index_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, price_index_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).mean = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mean = atof(arraydata);
	(*j)++;
	(*temp_datatype).sd = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sd = atof(arraydata);
	(*j)++;

	return 0;
}

int read_price_index_adt_dynamic_array(char * buffer, int buffer_size, int * j, price_index_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_price_index_adt(temp_datatype_array, 0.0, 0.0);
			rc = read_price_index_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'price_index_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_price_index_adt_static_array(char * buffer, int buffer_size, int * j, price_index_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_price_index_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'price_index_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_household_data(char * buffer, int * j, household_data * temp_datatype)
 * \brief Reads household_data datatype.
 */
int read_household_data(char * buffer, int /*@unused@*/ buffer_size, int * j, household_data * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).region_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_households = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_households = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_households_skill_1 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_households_skill_1 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_households_skill_2 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_households_skill_2 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_households_skill_3 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_households_skill_3 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_households_skill_4 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_households_skill_4 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_households_skill_5 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_households_skill_5 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employed = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employed = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employed_skill_1 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employed_skill_1 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employed_skill_2 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employed_skill_2 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employed_skill_3 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employed_skill_3 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employed_skill_4 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employed_skill_4 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employed_skill_5 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employed_skill_5 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).unemployed = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployed = atoi(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_2 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_2 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_3 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_3 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_4 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_4 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_5 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_5 = atof(arraydata);
	(*j)++;
	(*temp_datatype).consumption_budget = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).consumption_budget = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage_skill_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage_skill_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage_skill_2 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage_skill_2 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage_skill_3 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage_skill_3 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage_skill_4 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage_skill_4 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage_skill_5 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage_skill_5 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill_2 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill_2 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill_3 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill_3 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill_4 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill_4 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill_5 = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill_5 = atof(arraydata);
	(*j)++;

	return 0;
}

int read_household_data_dynamic_array(char * buffer, int buffer_size, int * j, household_data_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_household_data(temp_datatype_array, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_household_data(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'household_data' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_household_data_static_array(char * buffer, int buffer_size, int * j, household_data * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_household_data(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'household_data' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_firm_data(char * buffer, int * j, firm_data * temp_datatype)
 * \brief Reads firm_data datatype.
 */
int read_firm_data(char * buffer, int /*@unused@*/ buffer_size, int * j, firm_data * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).region_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_firms = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_firms = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_active_firms = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_active_firms = atoi(arraydata);
	(*j)++;
	(*temp_datatype).vacancies = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).vacancies = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employees = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employees = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employees_skill_1 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employees_skill_1 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employees_skill_2 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employees_skill_2 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employees_skill_3 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employees_skill_3 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employees_skill_4 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employees_skill_4 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employees_skill_5 = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employees_skill_5 = atoi(arraydata);
	(*j)++;
	(*temp_datatype).average_wage = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage_skill_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage_skill_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage_skill_2 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage_skill_2 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage_skill_3 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage_skill_3 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage_skill_4 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage_skill_4 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage_skill_5 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage_skill_5 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill_2 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill_2 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill_3 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill_3 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill_4 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill_4 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_s_skill_5 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_s_skill_5 = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_earnings = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_earnings = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_debt = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_debt = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_assets = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_assets = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_equity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_equity = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_debt_earnings_ratio = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_debt_earnings_ratio = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_debt_equity_ratio = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_debt_equity_ratio = atof(arraydata);
	(*j)++;
	(*temp_datatype).labour_share_ratio = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).labour_share_ratio = atof(arraydata);
	(*j)++;
	(*temp_datatype).monthly_sold_quantity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).monthly_sold_quantity = atof(arraydata);
	(*j)++;
	(*temp_datatype).monthly_output = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).monthly_output = atof(arraydata);
	(*j)++;
	(*temp_datatype).monthly_revenue = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).monthly_revenue = atof(arraydata);
	(*j)++;
	(*temp_datatype).monthly_planned_output = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).monthly_planned_output = atof(arraydata);
	(*j)++;
	(*temp_datatype).monthly_investment_value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).monthly_investment_value = atof(arraydata);
	(*j)++;
	(*temp_datatype).investment_gdp_ratio = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).investment_gdp_ratio = atof(arraydata);
	(*j)++;
	(*temp_datatype).gdp = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).gdp = atof(arraydata);
	(*j)++;
	(*temp_datatype).cpi = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).cpi = atof(arraydata);
	(*j)++;
	(*temp_datatype).cpi_last_month = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).cpi_last_month = atof(arraydata);
	(*j)++;
	(*temp_datatype).no_firm_births = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_firm_births = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_firm_deaths = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_firm_deaths = atoi(arraydata);
	(*j)++;
	(*temp_datatype).productivity_progress = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).productivity_progress = atof(arraydata);
	(*j)++;
	(*temp_datatype).productivity = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).productivity = atof(arraydata);
	(*j)++;

	return 0;
}

int read_firm_data_dynamic_array(char * buffer, int buffer_size, int * j, firm_data_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_firm_data(temp_datatype_array, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0.0, 0.0);
			rc = read_firm_data(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'firm_data' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_firm_data_static_array(char * buffer, int buffer_size, int * j, firm_data * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_firm_data(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'firm_data' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_region_data_item(char * buffer, int * j, region_data_item * temp_datatype)
 * \brief Reads region_data_item datatype.
 */
int read_region_data_item(char * buffer, int /*@unused@*/ buffer_size, int * j, region_data_item * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).cpi = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).cpi = atof(arraydata);
	(*j)++;
	(*temp_datatype).cpi_last_month = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).cpi_last_month = atof(arraydata);
	(*j)++;
	(*temp_datatype).gdp = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).gdp = atof(arraydata);
	(*j)++;
	(*temp_datatype).output = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).output = atof(arraydata);
	(*j)++;
	(*temp_datatype).employment = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employment = atoi(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_2 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_2 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_3 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_3 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_4 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_4 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_5 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_5 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage = atof(arraydata);
	(*j)++;
	(*temp_datatype).no_firms = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_firms = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_active_firms = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_active_firms = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_firm_births = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_firm_births = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_firm_deaths = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_firm_deaths = atoi(arraydata);
	(*j)++;
	(*temp_datatype).investment_value = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).investment_value = atof(arraydata);
	(*j)++;

	return 0;
}

int read_region_data_item_dynamic_array(char * buffer, int buffer_size, int * j, region_data_item_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_region_data_item(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0.0);
			rc = read_region_data_item(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'region_data_item' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_region_data_item_static_array(char * buffer, int buffer_size, int * j, region_data_item * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_region_data_item(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'region_data_item' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_history_item(char * buffer, int * j, history_item * temp_datatype)
 * \brief Reads history_item datatype.
 */
int read_history_item(char * buffer, int /*@unused@*/ buffer_size, int * j, history_item * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).cpi = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).cpi = atof(arraydata);
	(*j)++;
	(*temp_datatype).gdp = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).gdp = atof(arraydata);
	(*j)++;
	(*temp_datatype).output = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).output = atof(arraydata);
	(*j)++;
	(*temp_datatype).employment = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employment = atoi(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_2 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_2 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_3 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_3 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_4 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_4 = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_rate_skill_5 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_rate_skill_5 = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_wage = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_wage = atof(arraydata);
	(*j)++;
	(*temp_datatype).no_firms = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_firms = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_active_firms = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_active_firms = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_firm_births = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_firm_births = atoi(arraydata);
	(*j)++;
	(*temp_datatype).no_firm_deaths = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_firm_deaths = atoi(arraydata);
	(*j)++;
	(*temp_datatype).investment_value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).investment_value = atof(arraydata);
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_region_data_item_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).region_data);
	if(rc != 0) return -1;
	
	(*j)++;

	return 0;
}

int read_history_item_dynamic_array(char * buffer, int buffer_size, int * j, history_item_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	region_data_item_array region_data;
# ifndef S_SPLINT_S
	init_region_data_item_array(&region_data);
# endif

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_history_item(temp_datatype_array, 0.0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0.0, &region_data);
			rc = read_history_item(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'history_item' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_region_data_item_array(&region_data);
	
	
	return 0;
}

int read_history_item_static_array(char * buffer, int buffer_size, int * j, history_item * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_history_item(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'history_item' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_firm_stocks_adt(char * buffer, int * j, firm_stocks_adt * temp_datatype)
 * \brief Reads firm_stocks_adt datatype.
 */
int read_firm_stocks_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, firm_stocks_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).payment_account = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_value_local_inventory = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_value_local_inventory = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_value_capital_stock = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_value_capital_stock = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_assets = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_assets = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_debt = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_debt = atof(arraydata);
	(*j)++;
	(*temp_datatype).equity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).equity = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_liabilities = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_liabilities = atof(arraydata);
	(*j)++;
	(*temp_datatype).current_shares_outstanding = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).current_shares_outstanding = atoi(arraydata);
	(*j)++;
	(*temp_datatype).payment_account_day_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account_day_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).payment_account_day_20 = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account_day_20 = atof(arraydata);
	(*j)++;

	return 0;
}

int read_firm_stocks_adt_dynamic_array(char * buffer, int buffer_size, int * j, firm_stocks_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_firm_stocks_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0.0, 0.0);
			rc = read_firm_stocks_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'firm_stocks_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_firm_stocks_adt_static_array(char * buffer, int buffer_size, int * j, firm_stocks_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_firm_stocks_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'firm_stocks_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_firm_outflows_adt(char * buffer, int * j, firm_outflows_adt * temp_datatype)
 * \brief Reads firm_outflows_adt datatype.
 */
int read_firm_outflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, firm_outflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).labour_costs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).labour_costs = atof(arraydata);
	(*j)++;
	(*temp_datatype).capital_costs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).capital_costs = atof(arraydata);
	(*j)++;
	(*temp_datatype).energy_costs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).energy_costs = atof(arraydata);
	(*j)++;
	(*temp_datatype).tax_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).tax_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_debt_installment_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_debt_installment_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_interest_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_interest_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_dividend_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_dividend_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).value_of_repurchased_shares = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).value_of_repurchased_shares = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_expenses = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_expenses = atof(arraydata);
	(*j)++;

	return 0;
}

int read_firm_outflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, firm_outflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_firm_outflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_firm_outflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'firm_outflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_firm_outflows_adt_static_array(char * buffer, int buffer_size, int * j, firm_outflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_firm_outflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'firm_outflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_firm_inflows_adt(char * buffer, int * j, firm_inflows_adt * temp_datatype)
 * \brief Reads firm_inflows_adt datatype.
 */
int read_firm_inflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, firm_inflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).cum_revenue = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).cum_revenue = atof(arraydata);
	(*j)++;
	(*temp_datatype).new_loans = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).new_loans = atof(arraydata);
	(*j)++;
	(*temp_datatype).value_of_issued_shares = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).value_of_issued_shares = atof(arraydata);
	(*j)++;
	(*temp_datatype).subsidy = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).subsidy = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_income = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_income = atof(arraydata);
	(*j)++;
	(*temp_datatype).deposit_interest = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).deposit_interest = atof(arraydata);
	(*j)++;
	(*temp_datatype).net_inflow = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).net_inflow = atof(arraydata);
	(*j)++;

	return 0;
}

int read_firm_inflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, firm_inflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_firm_inflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_firm_inflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'firm_inflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_firm_inflows_adt_static_array(char * buffer, int buffer_size, int * j, firm_inflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_firm_inflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'firm_inflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_household_stocks_adt(char * buffer, int * j, household_stocks_adt * temp_datatype)
 * \brief Reads household_stocks_adt datatype.
 */
int read_household_stocks_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, household_stocks_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).payment_account = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account = atof(arraydata);
	(*j)++;
	(*temp_datatype).portfolio_value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).portfolio_value = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_assets = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_assets = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_liabilities = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_liabilities = atof(arraydata);
	(*j)++;
	(*temp_datatype).nr_assets = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).nr_assets = atoi(arraydata);
	(*j)++;
	(*temp_datatype).payment_account_day_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account_day_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).payment_account_day_20 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account_day_20 = atof(arraydata);
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_mortgage_contract_adt(buffer, buffer_size, j, &(*temp_datatype).mortgage_main_residence);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_mortgage_contract_adt(buffer, buffer_size, j, &(*temp_datatype).mortgage_other_property);
	if(rc != 0) return -1;
	(*j)++;
	(*temp_datatype).total_real_estate_value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_real_estate_value = atof(arraydata);
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_house_adt(buffer, buffer_size, j, &(*temp_datatype).main_residence);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_house_adt(buffer, buffer_size, j, &(*temp_datatype).other_property);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_rental_adt_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).rental_property_list);
	if(rc != 0) return -1;
	
	(*j)++;

	return 0;
}

int read_household_stocks_adt_dynamic_array(char * buffer, int buffer_size, int * j, household_stocks_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	mortgage_contract_adt mortgage_main_residence;
# ifndef S_SPLINT_S
	init_mortgage_contract_adt(&mortgage_main_residence);
# endif
	mortgage_contract_adt mortgage_other_property;
# ifndef S_SPLINT_S
	init_mortgage_contract_adt(&mortgage_other_property);
# endif
	
	house_adt main_residence;
# ifndef S_SPLINT_S
	init_house_adt(&main_residence);
# endif
	house_adt other_property;
# ifndef S_SPLINT_S
	init_house_adt(&other_property);
# endif
	
	
	rental_adt_array rental_property_list;
# ifndef S_SPLINT_S
	init_rental_adt_array(&rental_property_list);
# endif

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_household_stocks_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0, 0.0, 0.0, &mortgage_main_residence, &mortgage_other_property, 0.0, &main_residence, &other_property, &rental_property_list);
			rc = read_household_stocks_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'household_stocks_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_rental_adt_array(&rental_property_list);
	
	
	return 0;
}

int read_household_stocks_adt_static_array(char * buffer, int buffer_size, int * j, household_stocks_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_household_stocks_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'household_stocks_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_household_outflows_adt(char * buffer, int * j, household_outflows_adt * temp_datatype)
 * \brief Reads household_outflows_adt datatype.
 */
int read_household_outflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, household_outflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).consumption_expenditure = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).consumption_expenditure = atof(arraydata);
	(*j)++;
	(*temp_datatype).tax_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).tax_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).restitution_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).restitution_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).asset_purchases = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).asset_purchases = atof(arraydata);
	(*j)++;
	(*temp_datatype).mortgage_debt_service = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mortgage_debt_service = atof(arraydata);
	(*j)++;
	(*temp_datatype).rents = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).rents = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_expenses = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_expenses = atof(arraydata);
	(*j)++;

	return 0;
}

int read_household_outflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, household_outflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_household_outflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_household_outflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'household_outflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_household_outflows_adt_static_array(char * buffer, int buffer_size, int * j, household_outflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_household_outflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'household_outflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_household_inflows_adt(char * buffer, int * j, household_inflows_adt * temp_datatype)
 * \brief Reads household_inflows_adt datatype.
 */
int read_household_inflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, household_inflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).wage = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).wage = atof(arraydata);
	(*j)++;
	(*temp_datatype).unemployment_benefit = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).unemployment_benefit = atof(arraydata);
	(*j)++;
	(*temp_datatype).subsidies = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).subsidies = atof(arraydata);
	(*j)++;
	(*temp_datatype).transfer = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).transfer = atof(arraydata);
	(*j)++;
	(*temp_datatype).gov_interest = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).gov_interest = atof(arraydata);
	(*j)++;
	(*temp_datatype).asset_sales = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).asset_sales = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_dividends = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_dividends = atof(arraydata);
	(*j)++;
	(*temp_datatype).deposit_interest = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).deposit_interest = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_income = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_income = atof(arraydata);
	(*j)++;
	(*temp_datatype).mortgage_debt_service = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mortgage_debt_service = atof(arraydata);
	(*j)++;
	(*temp_datatype).mortgage_loan = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mortgage_loan = atof(arraydata);
	(*j)++;
	(*temp_datatype).rents = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).rents = atof(arraydata);
	(*j)++;
	(*temp_datatype).net_inflow = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).net_inflow = atof(arraydata);
	(*j)++;

	return 0;
}

int read_household_inflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, household_inflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_household_inflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_household_inflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'household_inflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_household_inflows_adt_static_array(char * buffer, int buffer_size, int * j, household_inflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_household_inflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'household_inflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_bank_stocks_adt(char * buffer, int * j, bank_stocks_adt * temp_datatype)
 * \brief Reads bank_stocks_adt datatype.
 */
int read_bank_stocks_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, bank_stocks_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).cash = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).cash = atof(arraydata);
	(*j)++;
	(*temp_datatype).reserves = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).reserves = atof(arraydata);
	(*j)++;
	(*temp_datatype).regulatory_reserves = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).regulatory_reserves = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_credit = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_credit = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_assets = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_assets = atof(arraydata);
	(*j)++;
	(*temp_datatype).deposits = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).deposits = atof(arraydata);
	(*j)++;
	(*temp_datatype).ecb_debt = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).ecb_debt = atof(arraydata);
	(*j)++;
	(*temp_datatype).equity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).equity = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_liabilities = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_liabilities = atof(arraydata);
	(*j)++;
	(*temp_datatype).current_shares_outstanding = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).current_shares_outstanding = atoi(arraydata);
	(*j)++;
	(*temp_datatype).cash_day_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).cash_day_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).cash_day_20 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).cash_day_20 = atof(arraydata);
	(*j)++;
	(*temp_datatype).loan_loss_reserve_firm_loans = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).loan_loss_reserve_firm_loans = atof(arraydata);
	(*j)++;
	(*temp_datatype).loan_loss_reserve_mortgage_loans = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).loan_loss_reserve_mortgage_loans = atof(arraydata);
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_mortgage_contract_adt_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).mortgage_portfolio);
	if(rc != 0) return -1;
	
	(*j)++;
	(*temp_datatype).total_mortgages = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_mortgages = atof(arraydata);
	(*j)++;

	return 0;
}

int read_bank_stocks_adt_dynamic_array(char * buffer, int buffer_size, int * j, bank_stocks_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	mortgage_contract_adt_array mortgage_portfolio;
# ifndef S_SPLINT_S
	init_mortgage_contract_adt_array(&mortgage_portfolio);
# endif
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_bank_stocks_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.0, &mortgage_portfolio, 0.0);
			rc = read_bank_stocks_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'bank_stocks_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_mortgage_contract_adt_array(&mortgage_portfolio);
	
	
	return 0;
}

int read_bank_stocks_adt_static_array(char * buffer, int buffer_size, int * j, bank_stocks_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_bank_stocks_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'bank_stocks_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_bank_outflows_adt(char * buffer, int * j, bank_outflows_adt * temp_datatype)
 * \brief Reads bank_outflows_adt datatype.
 */
int read_bank_outflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, bank_outflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).firm_loan_issues = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_loan_issues = atof(arraydata);
	(*j)++;
	(*temp_datatype).debt_installment_to_ecb = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).debt_installment_to_ecb = atof(arraydata);
	(*j)++;
	(*temp_datatype).ecb_interest_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).ecb_interest_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).deposit_interest_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).deposit_interest_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).dividend_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).dividend_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).tax_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).tax_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).deposit_outflow = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).deposit_outflow = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_expenses = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_expenses = atof(arraydata);
	(*j)++;
	(*temp_datatype).mortgage_loan_issues = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mortgage_loan_issues = atof(arraydata);
	(*j)++;

	return 0;
}

int read_bank_outflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, bank_outflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_bank_outflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_bank_outflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'bank_outflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_bank_outflows_adt_static_array(char * buffer, int buffer_size, int * j, bank_outflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_bank_outflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'bank_outflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_bank_inflows_adt(char * buffer, int * j, bank_inflows_adt * temp_datatype)
 * \brief Reads bank_inflows_adt datatype.
 */
int read_bank_inflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, bank_inflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).firm_loan_installments = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_loan_installments = atof(arraydata);
	(*j)++;
	(*temp_datatype).firm_interest_payments = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).firm_interest_payments = atof(arraydata);
	(*j)++;
	(*temp_datatype).new_ecb_debt = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).new_ecb_debt = atof(arraydata);
	(*j)++;
	(*temp_datatype).deposit_inflow = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).deposit_inflow = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_income = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_income = atof(arraydata);
	(*j)++;
	(*temp_datatype).net_inflow = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).net_inflow = atof(arraydata);
	(*j)++;
	(*temp_datatype).net_deposit_inflow = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).net_deposit_inflow = atof(arraydata);
	(*j)++;
	(*temp_datatype).mortgage_payments = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mortgage_payments = atof(arraydata);
	(*j)++;

	return 0;
}

int read_bank_inflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, bank_inflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_bank_inflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_bank_inflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'bank_inflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_bank_inflows_adt_static_array(char * buffer, int buffer_size, int * j, bank_inflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_bank_inflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'bank_inflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_gov_stocks_adt(char * buffer, int * j, gov_stocks_adt * temp_datatype)
 * \brief Reads gov_stocks_adt datatype.
 */
int read_gov_stocks_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, gov_stocks_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).payment_account = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_assets = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_assets = atof(arraydata);
	(*j)++;
	(*temp_datatype).value_bonds_outstanding = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).value_bonds_outstanding = atof(arraydata);
	(*j)++;
	(*temp_datatype).ecb_money = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).ecb_money = atof(arraydata);
	(*j)++;
	(*temp_datatype).equity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).equity = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_liabilities = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_liabilities = atof(arraydata);
	(*j)++;
	(*temp_datatype).nr_bonds_outstanding = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).nr_bonds_outstanding = atoi(arraydata);
	(*j)++;
	(*temp_datatype).payment_account_day_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account_day_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).payment_account_day_20 = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account_day_20 = atof(arraydata);
	(*j)++;

	return 0;
}

int read_gov_stocks_adt_dynamic_array(char * buffer, int buffer_size, int * j, gov_stocks_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_gov_stocks_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0.0, 0.0);
			rc = read_gov_stocks_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'gov_stocks_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_gov_stocks_adt_static_array(char * buffer, int buffer_size, int * j, gov_stocks_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_gov_stocks_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'gov_stocks_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_gov_outflows_adt(char * buffer, int * j, gov_outflows_adt * temp_datatype)
 * \brief Reads gov_outflows_adt datatype.
 */
int read_gov_outflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, gov_outflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).investment_expenditure = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).investment_expenditure = atof(arraydata);
	(*j)++;
	(*temp_datatype).consumption_expenditure = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).consumption_expenditure = atof(arraydata);
	(*j)++;
	(*temp_datatype).benefit_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).benefit_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).subsidy_payment_household = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).subsidy_payment_household = atof(arraydata);
	(*j)++;
	(*temp_datatype).subsidy_payment_firm = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).subsidy_payment_firm = atof(arraydata);
	(*j)++;
	(*temp_datatype).transfer_payment_household = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).transfer_payment_household = atof(arraydata);
	(*j)++;
	(*temp_datatype).transfer_payment_firm = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).transfer_payment_firm = atof(arraydata);
	(*j)++;
	(*temp_datatype).bond_interest_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).bond_interest_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).debt_installment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).debt_installment = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_bond_repurchase = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_bond_repurchase = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_expenses = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_expenses = atof(arraydata);
	(*j)++;

	return 0;
}

int read_gov_outflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, gov_outflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_gov_outflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_gov_outflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'gov_outflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_gov_outflows_adt_static_array(char * buffer, int buffer_size, int * j, gov_outflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_gov_outflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'gov_outflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_gov_inflows_adt(char * buffer, int * j, gov_inflows_adt * temp_datatype)
 * \brief Reads gov_inflows_adt datatype.
 */
int read_gov_inflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, gov_inflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).tax_revenues = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).tax_revenues = atof(arraydata);
	(*j)++;
	(*temp_datatype).restitution_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).restitution_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_bond_financing = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_bond_financing = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_money_financing = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_money_financing = atof(arraydata);
	(*j)++;
	(*temp_datatype).ecb_dividend = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).ecb_dividend = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_income = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_income = atof(arraydata);
	(*j)++;
	(*temp_datatype).net_inflow = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).net_inflow = atof(arraydata);
	(*j)++;

	return 0;
}

int read_gov_inflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, gov_inflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_gov_inflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_gov_inflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'gov_inflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_gov_inflows_adt_static_array(char * buffer, int buffer_size, int * j, gov_inflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_gov_inflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'gov_inflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_ecb_stocks_adt(char * buffer, int * j, ecb_stocks_adt * temp_datatype)
 * \brief Reads ecb_stocks_adt datatype.
 */
int read_ecb_stocks_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, ecb_stocks_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).cash = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).cash = atof(arraydata);
	(*j)++;
	(*temp_datatype).gov_bond_holdings = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).gov_bond_holdings = atof(arraydata);
	(*j)++;
	(*temp_datatype).fiat_money = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).fiat_money = atof(arraydata);
	(*j)++;
	(*temp_datatype).fiat_money_banks = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).fiat_money_banks = atof(arraydata);
	(*j)++;
	(*temp_datatype).fiat_money_govs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).fiat_money_govs = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_assets = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_assets = atof(arraydata);
	(*j)++;
	(*temp_datatype).payment_account_banks = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account_banks = atof(arraydata);
	(*j)++;
	(*temp_datatype).payment_account_govs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account_govs = atof(arraydata);
	(*j)++;
	(*temp_datatype).perpetuities_firms = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).perpetuities_firms = atof(arraydata);
	(*j)++;
	(*temp_datatype).perpetuities_banks = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).perpetuities_banks = atof(arraydata);
	(*j)++;
	(*temp_datatype).perpetuities_govs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).perpetuities_govs = atof(arraydata);
	(*j)++;
	(*temp_datatype).equity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).equity = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_liabilities = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_liabilities = atof(arraydata);
	(*j)++;
	(*temp_datatype).nr_gov_bonds = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).nr_gov_bonds = atoi(arraydata);
	(*j)++;
	(*temp_datatype).equity_day_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).equity_day_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).fiat_money_govs_bond = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).fiat_money_govs_bond = atof(arraydata);
	(*j)++;

	return 0;
}

int read_ecb_stocks_adt_dynamic_array(char * buffer, int buffer_size, int * j, ecb_stocks_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_ecb_stocks_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0.0, 0.0);
			rc = read_ecb_stocks_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'ecb_stocks_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_ecb_stocks_adt_static_array(char * buffer, int buffer_size, int * j, ecb_stocks_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_ecb_stocks_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'ecb_stocks_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_ecb_outflows_adt(char * buffer, int * j, ecb_outflows_adt * temp_datatype)
 * \brief Reads ecb_outflows_adt datatype.
 */
int read_ecb_outflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, ecb_outflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).gov_bond_purchase = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).gov_bond_purchase = atof(arraydata);
	(*j)++;
	(*temp_datatype).bank_fiat_money = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).bank_fiat_money = atof(arraydata);
	(*j)++;
	(*temp_datatype).bank_deposits = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).bank_deposits = atof(arraydata);
	(*j)++;
	(*temp_datatype).gov_deposits = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).gov_deposits = atof(arraydata);
	(*j)++;
	(*temp_datatype).dividend_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).dividend_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_expenses = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_expenses = atof(arraydata);
	(*j)++;

	return 0;
}

int read_ecb_outflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, ecb_outflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_ecb_outflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_ecb_outflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'ecb_outflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_ecb_outflows_adt_static_array(char * buffer, int buffer_size, int * j, ecb_outflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_ecb_outflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'ecb_outflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_ecb_inflows_adt(char * buffer, int * j, ecb_inflows_adt * temp_datatype)
 * \brief Reads ecb_inflows_adt datatype.
 */
int read_ecb_inflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, ecb_inflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).bank_interest = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).bank_interest = atof(arraydata);
	(*j)++;
	(*temp_datatype).bank_debt_installment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).bank_debt_installment = atof(arraydata);
	(*j)++;
	(*temp_datatype).gov_interest = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).gov_interest = atof(arraydata);
	(*j)++;
	(*temp_datatype).bank_deposits = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).bank_deposits = atof(arraydata);
	(*j)++;
	(*temp_datatype).gov_deposits = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).gov_deposits = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_income = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_income = atof(arraydata);
	(*j)++;
	(*temp_datatype).net_inflow = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).net_inflow = atof(arraydata);
	(*j)++;

	return 0;
}

int read_ecb_inflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, ecb_inflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_ecb_inflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_ecb_inflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'ecb_inflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_ecb_inflows_adt_static_array(char * buffer, int buffer_size, int * j, ecb_inflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_ecb_inflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'ecb_inflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_firm_balance_sheet_adt(char * buffer, int * j, firm_balance_sheet_adt * temp_datatype)
 * \brief Reads firm_balance_sheet_adt datatype.
 */
int read_firm_balance_sheet_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, firm_balance_sheet_adt * temp_datatype)
{
	
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[*j] != '{') (*j)++;
	rc = read_firm_stocks_adt(buffer, buffer_size, j, &(*temp_datatype).stocks);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_firm_outflows_adt(buffer, buffer_size, j, &(*temp_datatype).outflows);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_firm_inflows_adt(buffer, buffer_size, j, &(*temp_datatype).inflows);
	if(rc != 0) return -1;
	(*j)++;

	return 0;
}

int read_firm_balance_sheet_adt_dynamic_array(char * buffer, int buffer_size, int * j, firm_balance_sheet_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	firm_stocks_adt stocks;
# ifndef S_SPLINT_S
	init_firm_stocks_adt(&stocks);
# endif
	firm_outflows_adt outflows;
# ifndef S_SPLINT_S
	init_firm_outflows_adt(&outflows);
# endif
	firm_inflows_adt inflows;
# ifndef S_SPLINT_S
	init_firm_inflows_adt(&inflows);
# endif
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_firm_balance_sheet_adt(temp_datatype_array, &stocks, &outflows, &inflows);
			rc = read_firm_balance_sheet_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'firm_balance_sheet_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_firm_balance_sheet_adt_static_array(char * buffer, int buffer_size, int * j, firm_balance_sheet_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_firm_balance_sheet_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'firm_balance_sheet_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_household_balance_sheet_adt(char * buffer, int * j, household_balance_sheet_adt * temp_datatype)
 * \brief Reads household_balance_sheet_adt datatype.
 */
int read_household_balance_sheet_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, household_balance_sheet_adt * temp_datatype)
{
	
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[*j] != '{') (*j)++;
	rc = read_household_stocks_adt(buffer, buffer_size, j, &(*temp_datatype).stocks);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_household_outflows_adt(buffer, buffer_size, j, &(*temp_datatype).outflows);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_household_inflows_adt(buffer, buffer_size, j, &(*temp_datatype).inflows);
	if(rc != 0) return -1;
	(*j)++;

	return 0;
}

int read_household_balance_sheet_adt_dynamic_array(char * buffer, int buffer_size, int * j, household_balance_sheet_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	household_stocks_adt stocks;
# ifndef S_SPLINT_S
	init_household_stocks_adt(&stocks);
# endif
	household_outflows_adt outflows;
# ifndef S_SPLINT_S
	init_household_outflows_adt(&outflows);
# endif
	household_inflows_adt inflows;
# ifndef S_SPLINT_S
	init_household_inflows_adt(&inflows);
# endif
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_household_balance_sheet_adt(temp_datatype_array, &stocks, &outflows, &inflows);
			rc = read_household_balance_sheet_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'household_balance_sheet_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_household_balance_sheet_adt_static_array(char * buffer, int buffer_size, int * j, household_balance_sheet_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_household_balance_sheet_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'household_balance_sheet_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_bank_balance_sheet_adt(char * buffer, int * j, bank_balance_sheet_adt * temp_datatype)
 * \brief Reads bank_balance_sheet_adt datatype.
 */
int read_bank_balance_sheet_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, bank_balance_sheet_adt * temp_datatype)
{
	
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[*j] != '{') (*j)++;
	rc = read_bank_stocks_adt(buffer, buffer_size, j, &(*temp_datatype).stocks);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_bank_outflows_adt(buffer, buffer_size, j, &(*temp_datatype).outflows);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_bank_inflows_adt(buffer, buffer_size, j, &(*temp_datatype).inflows);
	if(rc != 0) return -1;
	(*j)++;

	return 0;
}

int read_bank_balance_sheet_adt_dynamic_array(char * buffer, int buffer_size, int * j, bank_balance_sheet_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	bank_stocks_adt stocks;
# ifndef S_SPLINT_S
	init_bank_stocks_adt(&stocks);
# endif
	bank_outflows_adt outflows;
# ifndef S_SPLINT_S
	init_bank_outflows_adt(&outflows);
# endif
	bank_inflows_adt inflows;
# ifndef S_SPLINT_S
	init_bank_inflows_adt(&inflows);
# endif
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_bank_balance_sheet_adt(temp_datatype_array, &stocks, &outflows, &inflows);
			rc = read_bank_balance_sheet_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'bank_balance_sheet_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_bank_balance_sheet_adt_static_array(char * buffer, int buffer_size, int * j, bank_balance_sheet_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_bank_balance_sheet_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'bank_balance_sheet_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_gov_balance_sheet_adt(char * buffer, int * j, gov_balance_sheet_adt * temp_datatype)
 * \brief Reads gov_balance_sheet_adt datatype.
 */
int read_gov_balance_sheet_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, gov_balance_sheet_adt * temp_datatype)
{
	
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[*j] != '{') (*j)++;
	rc = read_gov_stocks_adt(buffer, buffer_size, j, &(*temp_datatype).stocks);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_gov_outflows_adt(buffer, buffer_size, j, &(*temp_datatype).outflows);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_gov_inflows_adt(buffer, buffer_size, j, &(*temp_datatype).inflows);
	if(rc != 0) return -1;
	(*j)++;

	return 0;
}

int read_gov_balance_sheet_adt_dynamic_array(char * buffer, int buffer_size, int * j, gov_balance_sheet_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	gov_stocks_adt stocks;
# ifndef S_SPLINT_S
	init_gov_stocks_adt(&stocks);
# endif
	gov_outflows_adt outflows;
# ifndef S_SPLINT_S
	init_gov_outflows_adt(&outflows);
# endif
	gov_inflows_adt inflows;
# ifndef S_SPLINT_S
	init_gov_inflows_adt(&inflows);
# endif
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_gov_balance_sheet_adt(temp_datatype_array, &stocks, &outflows, &inflows);
			rc = read_gov_balance_sheet_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'gov_balance_sheet_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_gov_balance_sheet_adt_static_array(char * buffer, int buffer_size, int * j, gov_balance_sheet_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_gov_balance_sheet_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'gov_balance_sheet_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_ecb_balance_sheet_adt(char * buffer, int * j, ecb_balance_sheet_adt * temp_datatype)
 * \brief Reads ecb_balance_sheet_adt datatype.
 */
int read_ecb_balance_sheet_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, ecb_balance_sheet_adt * temp_datatype)
{
	
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[*j] != '{') (*j)++;
	rc = read_ecb_stocks_adt(buffer, buffer_size, j, &(*temp_datatype).stocks);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_ecb_outflows_adt(buffer, buffer_size, j, &(*temp_datatype).outflows);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_ecb_inflows_adt(buffer, buffer_size, j, &(*temp_datatype).inflows);
	if(rc != 0) return -1;
	(*j)++;

	return 0;
}

int read_ecb_balance_sheet_adt_dynamic_array(char * buffer, int buffer_size, int * j, ecb_balance_sheet_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	ecb_stocks_adt stocks;
# ifndef S_SPLINT_S
	init_ecb_stocks_adt(&stocks);
# endif
	ecb_outflows_adt outflows;
# ifndef S_SPLINT_S
	init_ecb_outflows_adt(&outflows);
# endif
	ecb_inflows_adt inflows;
# ifndef S_SPLINT_S
	init_ecb_inflows_adt(&inflows);
# endif
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_ecb_balance_sheet_adt(temp_datatype_array, &stocks, &outflows, &inflows);
			rc = read_ecb_balance_sheet_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'ecb_balance_sheet_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_ecb_balance_sheet_adt_static_array(char * buffer, int buffer_size, int * j, ecb_balance_sheet_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_ecb_balance_sheet_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'ecb_balance_sheet_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_igfirm_stocks_adt(char * buffer, int * j, igfirm_stocks_adt * temp_datatype)
 * \brief Reads igfirm_stocks_adt datatype.
 */
int read_igfirm_stocks_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, igfirm_stocks_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).payment_account = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_value_local_inventory = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_value_local_inventory = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_value_capital_stock = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_value_capital_stock = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_assets = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_assets = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_debt = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_debt = atof(arraydata);
	(*j)++;
	(*temp_datatype).equity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).equity = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_liabilities = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_liabilities = atof(arraydata);
	(*j)++;
	(*temp_datatype).current_shares_outstanding = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).current_shares_outstanding = atoi(arraydata);
	(*j)++;
	(*temp_datatype).payment_account_day_1 = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account_day_1 = atof(arraydata);
	(*j)++;
	(*temp_datatype).payment_account_day_20 = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account_day_20 = atof(arraydata);
	(*j)++;

	return 0;
}

int read_igfirm_stocks_adt_dynamic_array(char * buffer, int buffer_size, int * j, igfirm_stocks_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_igfirm_stocks_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0.0, 0.0);
			rc = read_igfirm_stocks_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'igfirm_stocks_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_igfirm_stocks_adt_static_array(char * buffer, int buffer_size, int * j, igfirm_stocks_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_igfirm_stocks_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'igfirm_stocks_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_igfirm_outflows_adt(char * buffer, int * j, igfirm_outflows_adt * temp_datatype)
 * \brief Reads igfirm_outflows_adt datatype.
 */
int read_igfirm_outflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, igfirm_outflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).labour_costs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).labour_costs = atof(arraydata);
	(*j)++;
	(*temp_datatype).capital_costs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).capital_costs = atof(arraydata);
	(*j)++;
	(*temp_datatype).energy_costs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).energy_costs = atof(arraydata);
	(*j)++;
	(*temp_datatype).tax_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).tax_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_debt_installment_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_debt_installment_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_interest_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_interest_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_dividend_payment = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_dividend_payment = atof(arraydata);
	(*j)++;
	(*temp_datatype).value_of_repurchased_shares = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).value_of_repurchased_shares = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_expenses = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_expenses = atof(arraydata);
	(*j)++;

	return 0;
}

int read_igfirm_outflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, igfirm_outflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_igfirm_outflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_igfirm_outflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'igfirm_outflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_igfirm_outflows_adt_static_array(char * buffer, int buffer_size, int * j, igfirm_outflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_igfirm_outflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'igfirm_outflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_igfirm_inflows_adt(char * buffer, int * j, igfirm_inflows_adt * temp_datatype)
 * \brief Reads igfirm_inflows_adt datatype.
 */
int read_igfirm_inflows_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, igfirm_inflows_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).cum_revenue = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).cum_revenue = atof(arraydata);
	(*j)++;
	(*temp_datatype).new_loans = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).new_loans = atof(arraydata);
	(*j)++;
	(*temp_datatype).value_of_issued_shares = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).value_of_issued_shares = atof(arraydata);
	(*j)++;
	(*temp_datatype).subsidy = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).subsidy = atof(arraydata);
	(*j)++;
	(*temp_datatype).total_income = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).total_income = atof(arraydata);
	(*j)++;
	(*temp_datatype).deposit_interest = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).deposit_interest = atof(arraydata);
	(*j)++;
	(*temp_datatype).net_inflow = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).net_inflow = atof(arraydata);
	(*j)++;

	return 0;
}

int read_igfirm_inflows_adt_dynamic_array(char * buffer, int buffer_size, int * j, igfirm_inflows_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_igfirm_inflows_adt(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_igfirm_inflows_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'igfirm_inflows_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_igfirm_inflows_adt_static_array(char * buffer, int buffer_size, int * j, igfirm_inflows_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_igfirm_inflows_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'igfirm_inflows_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_igfirm_balance_sheet_adt(char * buffer, int * j, igfirm_balance_sheet_adt * temp_datatype)
 * \brief Reads igfirm_balance_sheet_adt datatype.
 */
int read_igfirm_balance_sheet_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, igfirm_balance_sheet_adt * temp_datatype)
{
	
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[*j] != '{') (*j)++;
	rc = read_igfirm_stocks_adt(buffer, buffer_size, j, &(*temp_datatype).stocks);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_igfirm_outflows_adt(buffer, buffer_size, j, &(*temp_datatype).outflows);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_igfirm_inflows_adt(buffer, buffer_size, j, &(*temp_datatype).inflows);
	if(rc != 0) return -1;
	(*j)++;

	return 0;
}

int read_igfirm_balance_sheet_adt_dynamic_array(char * buffer, int buffer_size, int * j, igfirm_balance_sheet_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	igfirm_stocks_adt stocks;
# ifndef S_SPLINT_S
	init_igfirm_stocks_adt(&stocks);
# endif
	igfirm_outflows_adt outflows;
# ifndef S_SPLINT_S
	init_igfirm_outflows_adt(&outflows);
# endif
	igfirm_inflows_adt inflows;
# ifndef S_SPLINT_S
	init_igfirm_inflows_adt(&inflows);
# endif
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_igfirm_balance_sheet_adt(temp_datatype_array, &stocks, &outflows, &inflows);
			rc = read_igfirm_balance_sheet_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'igfirm_balance_sheet_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_igfirm_balance_sheet_adt_static_array(char * buffer, int buffer_size, int * j, igfirm_balance_sheet_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_igfirm_balance_sheet_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'igfirm_balance_sheet_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_consumption_goods_offer(char * buffer, int * j, consumption_goods_offer * temp_datatype)
 * \brief Reads consumption_goods_offer datatype.
 */
int read_consumption_goods_offer(char * buffer, int /*@unused@*/ buffer_size, int * j, consumption_goods_offer * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).quality = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quality = atof(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;

	return 0;
}

int read_consumption_goods_offer_dynamic_array(char * buffer, int buffer_size, int * j, consumption_goods_offer_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_consumption_goods_offer(temp_datatype_array, 0, 0.0, 0.0);
			rc = read_consumption_goods_offer(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'consumption_goods_offer' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_consumption_goods_offer_static_array(char * buffer, int buffer_size, int * j, consumption_goods_offer * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_consumption_goods_offer(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'consumption_goods_offer' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_estimators_linear_regression(char * buffer, int * j, estimators_linear_regression * temp_datatype)
 * \brief Reads estimators_linear_regression datatype.
 */
int read_estimators_linear_regression(char * buffer, int /*@unused@*/ buffer_size, int * j, estimators_linear_regression * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).mall_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mall_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).region_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).intercept = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).intercept = atof(arraydata);
	(*j)++;
	(*temp_datatype).regressor = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).regressor = atof(arraydata);
	(*j)++;
	(*temp_datatype).variance = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).variance = atof(arraydata);
	(*j)++;

	return 0;
}

int read_estimators_linear_regression_dynamic_array(char * buffer, int buffer_size, int * j, estimators_linear_regression_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_estimators_linear_regression(temp_datatype_array, 0, 0, 0.0, 0.0, 0.0);
			rc = read_estimators_linear_regression(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'estimators_linear_regression' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_estimators_linear_regression_static_array(char * buffer, int buffer_size, int * j, estimators_linear_regression * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_estimators_linear_regression(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'estimators_linear_regression' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_estimated_values_adt(char * buffer, int * j, estimated_values_adt * temp_datatype)
 * \brief Reads estimated_values_adt datatype.
 */
int read_estimated_values_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, estimated_values_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).no_positive_response = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_positive_response = atoi(arraydata);
	(*j)++;
	(*temp_datatype).probability = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).probability = atof(arraydata);
	(*j)++;
	(*temp_datatype).estimated_fix_costs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).estimated_fix_costs = atof(arraydata);
	(*j)++;
	(*temp_datatype).estimated_variable_costs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).estimated_variable_costs = atof(arraydata);
	(*j)++;
	(*temp_datatype).estimated_earnings = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).estimated_earnings = atof(arraydata);
	(*j)++;
	(*temp_datatype).additional_capital_Investments_depreciated = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).additional_capital_Investments_depreciated = atof(arraydata);
	(*j)++;
	(*temp_datatype).mean_specific_skills = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mean_specific_skills = atof(arraydata);
	(*j)++;
	(*temp_datatype).mean_wage = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mean_wage = atof(arraydata);
	(*j)++;
	(*temp_datatype).no_employees = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_employees = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_estimated_values_adt_dynamic_array(char * buffer, int buffer_size, int * j, estimated_values_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_estimated_values_adt(temp_datatype_array, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0);
			rc = read_estimated_values_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'estimated_values_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_estimated_values_adt_static_array(char * buffer, int buffer_size, int * j, estimated_values_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_estimated_values_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'estimated_values_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_market_research_price(char * buffer, int * j, dt_market_research_price * temp_datatype)
 * \brief Reads dt_market_research_price datatype.
 */
int read_dt_market_research_price(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_market_research_price * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).price_change = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price_change = atof(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_estimated_values_adt_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).estimated_values);
	if(rc != 0) return -1;
	
	(*j)++;

	return 0;
}

int read_dt_market_research_price_dynamic_array(char * buffer, int buffer_size, int * j, dt_market_research_price_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	estimated_values_adt_array estimated_values;
# ifndef S_SPLINT_S
	init_estimated_values_adt_array(&estimated_values);
# endif

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_market_research_price(temp_datatype_array, 0.0, 0.0, &estimated_values);
			rc = read_dt_market_research_price(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_market_research_price' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_estimated_values_adt_array(&estimated_values);
	
	
	return 0;
}

int read_dt_market_research_price_static_array(char * buffer, int buffer_size, int * j, dt_market_research_price * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_market_research_price(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_market_research_price' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_market_research_qualities(char * buffer, int * j, dt_market_research_qualities * temp_datatype)
 * \brief Reads dt_market_research_qualities datatype.
 */
int read_dt_market_research_qualities(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_market_research_qualities * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).quality = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quality = atof(arraydata);
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_dt_market_research_price_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).market_research_price);
	if(rc != 0) return -1;
	
	(*j)++;

	return 0;
}

int read_dt_market_research_qualities_dynamic_array(char * buffer, int buffer_size, int * j, dt_market_research_qualities_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	dt_market_research_price_array market_research_price;
# ifndef S_SPLINT_S
	init_dt_market_research_price_array(&market_research_price);
# endif

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_market_research_qualities(temp_datatype_array, 0.0, &market_research_price);
			rc = read_dt_market_research_qualities(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_market_research_qualities' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_dt_market_research_price_array(&market_research_price);
	
	
	return 0;
}

int read_dt_market_research_qualities_static_array(char * buffer, int buffer_size, int * j, dt_market_research_qualities * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_market_research_qualities(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_market_research_qualities' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_best_price_strategies(char * buffer, int * j, dt_best_price_strategies * temp_datatype)
 * \brief Reads dt_best_price_strategies datatype.
 */
int read_dt_best_price_strategies(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_best_price_strategies * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).quality = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quality = atof(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;
	(*temp_datatype).expected_earnings = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).expected_earnings = atof(arraydata);
	(*j)++;
	(*temp_datatype).sum_earnings = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sum_earnings = atof(arraydata);
	(*j)++;
	(*temp_datatype).sum_expected_earnings_discounted = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sum_expected_earnings_discounted = atof(arraydata);
	(*j)++;

	return 0;
}

int read_dt_best_price_strategies_dynamic_array(char * buffer, int buffer_size, int * j, dt_best_price_strategies_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_best_price_strategies(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_dt_best_price_strategies(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_best_price_strategies' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_dt_best_price_strategies_static_array(char * buffer, int buffer_size, int * j, dt_best_price_strategies * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_best_price_strategies(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_best_price_strategies' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_price_range(char * buffer, int * j, dt_price_range * temp_datatype)
 * \brief Reads dt_price_range datatype.
 */
int read_dt_price_range(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_price_range * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).start_price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).start_price = atof(arraydata);
	(*j)++;
	(*temp_datatype).end_price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).end_price = atof(arraydata);
	(*j)++;
	(*temp_datatype).increment = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).increment = atof(arraydata);
	(*j)++;

	return 0;
}

int read_dt_price_range_dynamic_array(char * buffer, int buffer_size, int * j, dt_price_range_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_price_range(temp_datatype_array, 0.0, 0.0, 0.0);
			rc = read_dt_price_range(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_price_range' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_dt_price_range_static_array(char * buffer, int buffer_size, int * j, dt_price_range * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_price_range(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_price_range' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_prospective_variables(char * buffer, int * j, dt_prospective_variables * temp_datatype)
 * \brief Reads dt_prospective_variables datatype.
 */
int read_dt_prospective_variables(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_prospective_variables * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).mean_specific_skills = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mean_specific_skills = atof(arraydata);
	(*j)++;
	(*temp_datatype).estimated_mean_wage = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).estimated_mean_wage = atof(arraydata);
	(*j)++;
	(*temp_datatype).no_employees = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).no_employees = atof(arraydata);
	(*j)++;
	(*temp_datatype).earnings = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).earnings = atof(arraydata);
	(*j)++;
	(*temp_datatype).payment_account = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).payment_account = atof(arraydata);
	(*j)++;
	(*temp_datatype).buffer = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).buffer = atof(arraydata);
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_adt_capital_stock_vintages_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).capital_stock_vintages);
	if(rc != 0) return -1;
	
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_financing_capital_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).capital_financing);
	if(rc != 0) return -1;
	
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_debt_item_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).loans);
	if(rc != 0) return -1;
	
	(*j)++;

	return 0;
}

int read_dt_prospective_variables_dynamic_array(char * buffer, int buffer_size, int * j, dt_prospective_variables_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	adt_capital_stock_vintages_array capital_stock_vintages;
# ifndef S_SPLINT_S
	init_adt_capital_stock_vintages_array(&capital_stock_vintages);
# endif
	
	financing_capital_array capital_financing;
# ifndef S_SPLINT_S
	init_financing_capital_array(&capital_financing);
# endif
	
	debt_item_array loans;
# ifndef S_SPLINT_S
	init_debt_item_array(&loans);
# endif

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_prospective_variables(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, &capital_stock_vintages, &capital_financing, &loans);
			rc = read_dt_prospective_variables(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_prospective_variables' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_adt_capital_stock_vintages_array(&capital_stock_vintages);
	free_financing_capital_array(&capital_financing);
	free_debt_item_array(&loans);
	
	
	return 0;
}

int read_dt_prospective_variables_static_array(char * buffer, int buffer_size, int * j, dt_prospective_variables * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_prospective_variables(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_prospective_variables' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_variables_changed(char * buffer, int * j, dt_variables_changed * temp_datatype)
 * \brief Reads dt_variables_changed datatype.
 */
int read_dt_variables_changed(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_variables_changed * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).price_index = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price_index = atof(arraydata);
	(*j)++;
	(*temp_datatype).quality_index = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quality_index = atof(arraydata);
	(*j)++;
	(*temp_datatype).productivity_progress = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).productivity_progress = atof(arraydata);
	(*j)++;

	return 0;
}

int read_dt_variables_changed_dynamic_array(char * buffer, int buffer_size, int * j, dt_variables_changed_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_variables_changed(temp_datatype_array, 0.0, 0.0, 0.0);
			rc = read_dt_variables_changed(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_variables_changed' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_dt_variables_changed_static_array(char * buffer, int buffer_size, int * j, dt_variables_changed * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_variables_changed(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_variables_changed' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_innovation_choice(char * buffer, int * j, dt_innovation_choice * temp_datatype)
 * \brief Reads dt_innovation_choice datatype.
 */
int read_dt_innovation_choice(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_innovation_choice * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).development_period = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).development_period = atoi(arraydata);
	(*j)++;
	(*temp_datatype).employees_needed = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).employees_needed = atoi(arraydata);
	(*j)++;
	(*temp_datatype).quality = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quality = atof(arraydata);
	(*j)++;
	(*temp_datatype).expected_discounted_earnings = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).expected_discounted_earnings = atof(arraydata);
	(*j)++;

	return 0;
}

int read_dt_innovation_choice_dynamic_array(char * buffer, int buffer_size, int * j, dt_innovation_choice_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_innovation_choice(temp_datatype_array, 0, 0, 0.0, 0.0);
			rc = read_dt_innovation_choice(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_innovation_choice' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_dt_innovation_choice_static_array(char * buffer, int buffer_size, int * j, dt_innovation_choice * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_innovation_choice(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_innovation_choice' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_demand_function(char * buffer, int * j, dt_demand_function * temp_datatype)
 * \brief Reads dt_demand_function datatype.
 */
int read_dt_demand_function(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_demand_function * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).quality = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quality = atof(arraydata);
	(*j)++;
	(*temp_datatype).year = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).year = atoi(arraydata);
	(*j)++;
	(*temp_datatype).factor = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).factor = atof(arraydata);
	(*j)++;
	(*temp_datatype).exponent = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).exponent = atof(arraydata);
	(*j)++;
	(*temp_datatype).variance = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).variance = atof(arraydata);
	(*j)++;

	return 0;
}

int read_dt_demand_function_dynamic_array(char * buffer, int buffer_size, int * j, dt_demand_function_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_demand_function(temp_datatype_array, 0.0, 0, 0.0, 0.0, 0.0);
			rc = read_dt_demand_function(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_demand_function' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_dt_demand_function_static_array(char * buffer, int buffer_size, int * j, dt_demand_function * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_demand_function(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_demand_function' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_price_quantity_touple(char * buffer, int * j, dt_price_quantity_touple * temp_datatype)
 * \brief Reads dt_price_quantity_touple datatype.
 */
int read_dt_price_quantity_touple(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_price_quantity_touple * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;
	(*temp_datatype).quantity = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).quantity = atof(arraydata);
	(*j)++;

	return 0;
}

int read_dt_price_quantity_touple_dynamic_array(char * buffer, int buffer_size, int * j, dt_price_quantity_touple_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_price_quantity_touple(temp_datatype_array, 0.0, 0.0);
			rc = read_dt_price_quantity_touple(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_price_quantity_touple' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_dt_price_quantity_touple_static_array(char * buffer, int buffer_size, int * j, dt_price_quantity_touple * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_price_quantity_touple(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_price_quantity_touple' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_market_size(char * buffer, int * j, dt_market_size * temp_datatype)
 * \brief Reads dt_market_size datatype.
 */
int read_dt_market_size(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_market_size * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).period = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).period = atoi(arraydata);
	(*j)++;
	(*temp_datatype).market_size = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).market_size = atof(arraydata);
	(*j)++;

	return 0;
}

int read_dt_market_size_dynamic_array(char * buffer, int buffer_size, int * j, dt_market_size_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_market_size(temp_datatype_array, 0, 0.0);
			rc = read_dt_market_size(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_market_size' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_dt_market_size_static_array(char * buffer, int buffer_size, int * j, dt_market_size * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_market_size(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_market_size' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_total_and_regional_market_size(char * buffer, int * j, dt_total_and_regional_market_size * temp_datatype)
 * \brief Reads dt_total_and_regional_market_size datatype.
 */
int read_dt_total_and_regional_market_size(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_total_and_regional_market_size * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).region_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).region_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).mall_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mall_id = atoi(arraydata);
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_dt_market_size_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).market_sizes);
	if(rc != 0) return -1;
	
	(*j)++;

	return 0;
}

int read_dt_total_and_regional_market_size_dynamic_array(char * buffer, int buffer_size, int * j, dt_total_and_regional_market_size_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	dt_market_size_array market_sizes;
# ifndef S_SPLINT_S
	init_dt_market_size_array(&market_sizes);
# endif

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_total_and_regional_market_size(temp_datatype_array, 0, 0, &market_sizes);
			rc = read_dt_total_and_regional_market_size(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_total_and_regional_market_size' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_dt_market_size_array(&market_sizes);
	
	
	return 0;
}

int read_dt_total_and_regional_market_size_static_array(char * buffer, int buffer_size, int * j, dt_total_and_regional_market_size * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_total_and_regional_market_size(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_total_and_regional_market_size' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_value_lattice(char * buffer, int * j, dt_value_lattice * temp_datatype)
 * \brief Reads dt_value_lattice datatype.
 */
int read_dt_value_lattice(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_value_lattice * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).intermediate_quality = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).intermediate_quality = atof(arraydata);
	(*j)++;
	(*temp_datatype).value = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).value = atof(arraydata);
	(*j)++;
	(*temp_datatype).strategy = 0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).strategy = atoi(arraydata);
	(*j)++;

	return 0;
}

int read_dt_value_lattice_dynamic_array(char * buffer, int buffer_size, int * j, dt_value_lattice_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_value_lattice(temp_datatype_array, 0.0, 0.0, 0);
			rc = read_dt_value_lattice(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_value_lattice' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_dt_value_lattice_static_array(char * buffer, int buffer_size, int * j, dt_value_lattice * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_value_lattice(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_value_lattice' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_value_lattice_years(char * buffer, int * j, dt_value_lattice_years * temp_datatype)
 * \brief Reads dt_value_lattice_years datatype.
 */
int read_dt_value_lattice_years(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_value_lattice_years * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).year = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).year = atoi(arraydata);
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_dt_value_lattice_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).values);
	if(rc != 0) return -1;
	
	(*j)++;

	return 0;
}

int read_dt_value_lattice_years_dynamic_array(char * buffer, int buffer_size, int * j, dt_value_lattice_years_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	dt_value_lattice_array values;
# ifndef S_SPLINT_S
	init_dt_value_lattice_array(&values);
# endif

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_value_lattice_years(temp_datatype_array, 0, &values);
			rc = read_dt_value_lattice_years(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_value_lattice_years' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_dt_value_lattice_array(&values);
	
	
	return 0;
}

int read_dt_value_lattice_years_static_array(char * buffer, int buffer_size, int * j, dt_value_lattice_years * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_value_lattice_years(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_value_lattice_years' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_dt_monthly_estimations(char * buffer, int * j, dt_monthly_estimations * temp_datatype)
 * \brief Reads dt_monthly_estimations datatype.
 */
int read_dt_monthly_estimations(char * buffer, int /*@unused@*/ buffer_size, int * j, dt_monthly_estimations * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).output = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).output = atof(arraydata);
	(*j)++;
	(*temp_datatype).earnings = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).earnings = atof(arraydata);
	(*j)++;
	(*temp_datatype).sold_quantity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).sold_quantity = atof(arraydata);
	(*j)++;
	(*temp_datatype).labor_costs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).labor_costs = atof(arraydata);
	(*j)++;
	(*temp_datatype).capital_costs = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).capital_costs = atof(arraydata);
	(*j)++;
	(*temp_datatype).interest_payments = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).interest_payments = atof(arraydata);
	(*j)++;
	(*temp_datatype).wage = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).wage = atof(arraydata);
	(*j)++;
	(*temp_datatype).mean_specific_skills = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).mean_specific_skills = atof(arraydata);
	(*j)++;
	(*temp_datatype).average_productivity = 0.0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).average_productivity = atof(arraydata);
	(*j)++;
	(*temp_datatype).investment_nominal = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).investment_nominal = atof(arraydata);
	(*j)++;

	return 0;
}

int read_dt_monthly_estimations_dynamic_array(char * buffer, int buffer_size, int * j, dt_monthly_estimations_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	
	
	
	
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_dt_monthly_estimations(temp_datatype_array, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			rc = read_dt_monthly_estimations(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'dt_monthly_estimations' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_dt_monthly_estimations_static_array(char * buffer, int buffer_size, int * j, dt_monthly_estimations * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_dt_monthly_estimations(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'dt_monthly_estimations' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_bid_adt(char * buffer, int * j, bid_adt * temp_datatype)
 * \brief Reads bid_adt datatype.
 */
int read_bid_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, bid_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;

	return 0;
}

int read_bid_adt_dynamic_array(char * buffer, int buffer_size, int * j, bid_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_bid_adt(temp_datatype_array, 0, 0.0);
			rc = read_bid_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'bid_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_bid_adt_static_array(char * buffer, int buffer_size, int * j, bid_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_bid_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'bid_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_ask_adt(char * buffer, int * j, ask_adt * temp_datatype)
 * \brief Reads ask_adt datatype.
 */
int read_ask_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, ask_adt * temp_datatype)
{
	int array_k;
	char arraydata[100000];
	
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	(*temp_datatype).object_id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).object_id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).id = 0;
	array_k = 0;
	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).id = atoi(arraydata);
	(*j)++;
	(*temp_datatype).price = 0.0;
	array_k = 0;
	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		arraydata[array_k] = buffer[*j];
		array_k++;
		(*j)++;
	}
	arraydata[array_k] = '\0';
	(*temp_datatype).price = atof(arraydata);
	(*j)++;

	return 0;
}

int read_ask_adt_dynamic_array(char * buffer, int buffer_size, int * j, ask_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_ask_adt(temp_datatype_array, 0, 0, 0.0);
			rc = read_ask_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'ask_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_ask_adt_static_array(char * buffer, int buffer_size, int * j, ask_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_ask_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'ask_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_auction_orders_adt(char * buffer, int * j, auction_orders_adt * temp_datatype)
 * \brief Reads auction_orders_adt datatype.
 */
int read_auction_orders_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, auction_orders_adt * temp_datatype)
{
	
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[*j] != '{') (*j)++;

	rc = read_bid_adt_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).bids);
	if(rc != 0) return -1;
	
	(*j)++;
	while(buffer[*j] != '{') (*j)++;

	rc = read_ask_adt_dynamic_array(buffer, buffer_size, j, &(*temp_datatype).asks);
	if(rc != 0) return -1;
	
	(*j)++;

	return 0;
}

int read_auction_orders_adt_dynamic_array(char * buffer, int buffer_size, int * j, auction_orders_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	
	bid_adt_array bids;
# ifndef S_SPLINT_S
	init_bid_adt_array(&bids);
# endif
	
	ask_adt_array asks;
# ifndef S_SPLINT_S
	init_ask_adt_array(&asks);
# endif

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_auction_orders_adt(temp_datatype_array, &bids, &asks);
			rc = read_auction_orders_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'auction_orders_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	free_bid_adt_array(&bids);
	free_ask_adt_array(&asks);
	
	
	return 0;
}

int read_auction_orders_adt_static_array(char * buffer, int buffer_size, int * j, auction_orders_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_auction_orders_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'auction_orders_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}

/** \fn void read_auction_adt(char * buffer, int * j, auction_adt * temp_datatype)
 * \brief Reads auction_adt datatype.
 */
int read_auction_adt(char * buffer, int /*@unused@*/ buffer_size, int * j, auction_adt * temp_datatype)
{
	
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[*j] != '{') (*j)++;
	rc = read_auction_orders_adt(buffer, buffer_size, j, &(*temp_datatype).pending);
	if(rc != 0) return -1;
	(*j)++;
	while(buffer[*j] != '{') (*j)++;
	rc = read_auction_orders_adt(buffer, buffer_size, j, &(*temp_datatype).unprocessed);
	if(rc != 0) return -1;
	(*j)++;

	return 0;
}

int read_auction_adt_dynamic_array(char * buffer, int buffer_size, int * j, auction_adt_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	auction_orders_adt pending;
# ifndef S_SPLINT_S
	init_auction_orders_adt(&pending);
# endif
	auction_orders_adt unprocessed;
# ifndef S_SPLINT_S
	init_auction_orders_adt(&unprocessed);
# endif
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_auction_adt(temp_datatype_array, &pending, &unprocessed);
			rc = read_auction_adt(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'auction_adt' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_auction_adt_static_array(char * buffer, int buffer_size, int * j, auction_adt * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_auction_adt(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'auction_adt' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}



int readEnvironmentXML(char * location)
{
	FILE * file;
	char c = '\0';
	char buffer[100000];
	int index = 0;
	int in_environment = 0;
	int in_rnd_seed = 0;
	int in_GSL_RNG_SEED = 0;
	int in_total_regions = 0;
	int in_id_debug_probe = 0;
	int in_print_debug_id_probe = 0;
	int in_time_debug_probe = 0;
	int in_print_log = 0;
	int in_print_debug_bankruptcy = 0;
	int in_print_debug_eurostat = 0;
	int in_print_debug_ch = 0;
	int in_print_debug_afm = 0;
	int in_print_debug_afm_ch = 0;
	int in_print_debug_exp1 = 0;
	int in_print_debug_file_exp1 = 0;
	int in_print_debug_file_exp2 = 0;
	int in_policy_exp1 = 0;
	int in_print_debug_gov = 0;
	int in_print_debug_household = 0;
	int in_print_debug_credit = 0;
	int in_print_debug_nsa = 0;
	int in_print_debug_consumption = 0;
	int in_print_debug_finman = 0;
	int in_print_debug_production = 0;
	int in_print_debug_mall = 0;
	int in_print_debug = 0;
	int in_print_debug_market_research = 0;
	int in_print_debug_credit_risk_mngt = 0;
	int in_print_debug_credit_unittest = 0;
	int in_print_debug_housing = 0;
	int in_print_debug_housing_unittest = 0;
	int in_print_debug_rental = 0;
	int in_print_debug_rental_unittest = 0;
	int in_switch_behavioral_state_transitions_housing = 0;
	int in_print_debug_mortgage = 0;
	int in_print_debug_mortgage_hh = 0;
	int in_policy_exp_energy_shock = 0;
	int in_policy_exp_stabilization_subsidy = 0;
	int in_policy_exp_stabilization_tax = 0;
	int in_const_bankruptcy_idle_period = 0;
	int in_days_per_month = 0;
	int in_xml_cloned = 0;
	int in_transition_phase_innov = 0;
	int in_transition_phase_recap = 0;
	int in_const_init_transient_period = 0;
	int in_individual_learning = 0;
	int in_const_wage_wealth_ratio = 0;
	int in_const_income_tax_rate = 0;
	int in_gamma_const = 0;
	int in_gamma_quality = 0;
	int in_depreciation_rate = 0;
	int in_discont_rate = 0;
	int in_mark_up = 0;
	int in_lambda = 0;
	int in_target_savings_rate = 0;
	int in_carrol_consumption_parameter = 0;
	int in_quantil_normal_distribution = 0;
	int in_firm_planning_horizon = 0;
	int in_adaption_delivery_volume = 0;
	int in_inv_inertia = 0;
	int in_gamma_logit_vintage_choice = 0;
	int in_delta_logit_vintage_choice = 0;
	int in_housing_alpha = 0;
	int in_housing_beta = 0;
	int in_housing_gamma = 0;
	int in_const_mortgage_initial_risk_of_default = 0;
	int in_const_corporate_initial_risk_of_default = 0;
	int in_max_duration_firm_loans_arrears = 0;
	int in_max_duration_firm_loans_npl = 0;
	int in_max_duration_mortgage_loans_arrears = 0;
	int in_max_duration_mortgage_loans_npl = 0;
	int in_max_dsti_for_repayment = 0;
	int in_max_id = 0;
	int in_number_of_banks_to_apply = 0;
	int in_const_number_of_banks = 0;
	int in_const_installment_periods = 0;
	int in_const_bank_dividend_rate = 0;
	int in_bank_lambda = 0;
	int in_ecb_interest_rate = 0;
	int in_ecb_interest_rate_markdown = 0;
	int in_alfa = 0;
	int in_min_reserve_ratio = 0;
	int in_const_init_pd_corp = 0;
	int in_const_init_lgd_corp = 0;
	int in_const_init_pd_hh = 0;
	int in_const_init_lgd_hh = 0;
	int in_switch_bank_liquidity_full_rationing = 0;
	int in_switch_bank_capital_full_rationing = 0;
	int in_switch_non_risk_weighted_car = 0;
	int in_switch_ban_bank_dividends = 0;
	int in_switch_credit_rationing_unsound_firms = 0;
	int in_switch_credit_rationing_ponzi_firms = 0;
	int in_bank_data_quantile_upper_bound = 0;
	int in_bank_data_quantile_lower_bound = 0;
	int in_const_firm_leverage = 0;
	int in_debt_rescaling_factor = 0;
	int in_target_leverage_ratio = 0;
	int in_target_liquidity_ratio = 0;
	int in_const_dividend_earnings_ratio = 0;
	int in_switch_threshold_full_dividend_rule = 0;
	int in_const_threshold_full_dividend_rule = 0;
	int in_switch_firm_illiquidity_debt_rescaling_rule = 0;
	int in_igfirm_dividend_payout_stretching_month = 0;
	int in_index_price_adj = 0;
	int in_index_price_adj_max = 0;
	int in_index_price_adj_min = 0;
	int in_trading_activity = 0;
	int in_trading_random = 0;
	int in_igfirm_fin_man_debug = 0;
	int in_switch_igfirm_endogenous_innovation_probability = 0;
	int in_igfirm_exogenous_innovation_probability = 0;
	int in_power_of_end_probability_function = 0;
	int in_igfirm_producer_debug = 0;
	int in_igfirm_exogenous_productivity_progress = 0;
	int in_symmetric_shock = 0;
	int in_energy_shock_start = 0;
	int in_energy_shock_end = 0;
	int in_const_energy_shock_intensity = 0;
	int in_energy_shock_frequency = 0;
	int in_innovation_by_random = 0;
	int in_ig_good_limited_offer = 0;
	int in_max_offer_ig_good = 0;
	int in_initial_frontier_firm_transition_phase = 0;
	int in_initial_productivity_firm = 0;
	int in_initial_specific_skills = 0;
	int in_strenght_of_tech_progress = 0;
	int in_linear_combination_pricing_ig_good = 0;
	int in_initial_capital_price_wage_ratio = 0;
	int in_union_strength = 0;
	int in_wage_update = 0;
	int in_min_vacancy = 0;
	int in_wage_reservation_update = 0;
	int in_region_cost = 0;
	int in_delivery_prob_if_critical_stock_0 = 0;
	int in_number_applications = 0;
	int in_applications_per_day = 0;
	int in_lower_bound_firing = 0;
	int in_upper_bound_firing = 0;
	int in_logit_parameter_specific_skills = 0;
	int in_logit_parameter_general_skills = 0;
	int in_skill_update_acc_to_formula = 0;
	int in_gov_policy_unemployment_benefit_pct = 0;
	int in_gov_policy_money_financing_fraction = 0;
	int in_gov_policy_gdp_fraction_consumption = 0;
	int in_gov_policy_gdp_fraction_investment = 0;
	int in_no_regions_per_gov = 0;
	int in_subsidy_trigger_on = 0;
	int in_subsidy_trigger_off = 0;
	int in_gov_policy_swith_quantitative_easing = 0;
	int in_gov_policy_switch_human_capital_improvement = 0;
	int in_policy_exp_best_technology_subsidy = 0;
	int in_regional_policy_technology_subsidy = 0;
	int in_best_technology_subsidy_pct = 0;
	int in_innovation_switched_on = 0;
	int in_mr_start_price = 0;
	int in_mr_end_price = 0;
	int in_mr_price_increment = 0;
	int in_max_no_employees_product_innovation = 0;
	

	buffer[0] = '\0';

	/* Open file */
	if((file = fopen(location, "r"))==NULL)
	{
		printf("Error: cannot open import xml file '%s'\n", location);
		exit(0);
	}
	printf("Reading environment data from: %s\n", location);
	/* Keep reading file until EOF */
	while(c != (char)EOF)
	{
		/* Get the next char from the file */
		c = (char)fgetc(file);
		if(c == '>')
		{
			buffer[index] = '\0';
			if(strcmp(buffer, "environment") == 0) in_environment = 1;
			if(strcmp(buffer, "/environment") == 0) in_environment = 0;
			if(strcmp(buffer, "rnd_seed") == 0) in_rnd_seed = 1;
			if(strcmp(buffer, "/rnd_seed") == 0) in_rnd_seed = 0;
			if(strcmp(buffer, "GSL_RNG_SEED") == 0) in_GSL_RNG_SEED = 1;
			if(strcmp(buffer, "/GSL_RNG_SEED") == 0) in_GSL_RNG_SEED = 0;
			if(strcmp(buffer, "total_regions") == 0) in_total_regions = 1;
			if(strcmp(buffer, "/total_regions") == 0) in_total_regions = 0;
			if(strcmp(buffer, "id_debug_probe") == 0) in_id_debug_probe = 1;
			if(strcmp(buffer, "/id_debug_probe") == 0) in_id_debug_probe = 0;
			if(strcmp(buffer, "print_debug_id_probe") == 0) in_print_debug_id_probe = 1;
			if(strcmp(buffer, "/print_debug_id_probe") == 0) in_print_debug_id_probe = 0;
			if(strcmp(buffer, "time_debug_probe") == 0) in_time_debug_probe = 1;
			if(strcmp(buffer, "/time_debug_probe") == 0) in_time_debug_probe = 0;
			if(strcmp(buffer, "print_log") == 0) in_print_log = 1;
			if(strcmp(buffer, "/print_log") == 0) in_print_log = 0;
			if(strcmp(buffer, "print_debug_bankruptcy") == 0) in_print_debug_bankruptcy = 1;
			if(strcmp(buffer, "/print_debug_bankruptcy") == 0) in_print_debug_bankruptcy = 0;
			if(strcmp(buffer, "print_debug_eurostat") == 0) in_print_debug_eurostat = 1;
			if(strcmp(buffer, "/print_debug_eurostat") == 0) in_print_debug_eurostat = 0;
			if(strcmp(buffer, "print_debug_ch") == 0) in_print_debug_ch = 1;
			if(strcmp(buffer, "/print_debug_ch") == 0) in_print_debug_ch = 0;
			if(strcmp(buffer, "print_debug_afm") == 0) in_print_debug_afm = 1;
			if(strcmp(buffer, "/print_debug_afm") == 0) in_print_debug_afm = 0;
			if(strcmp(buffer, "print_debug_afm_ch") == 0) in_print_debug_afm_ch = 1;
			if(strcmp(buffer, "/print_debug_afm_ch") == 0) in_print_debug_afm_ch = 0;
			if(strcmp(buffer, "print_debug_exp1") == 0) in_print_debug_exp1 = 1;
			if(strcmp(buffer, "/print_debug_exp1") == 0) in_print_debug_exp1 = 0;
			if(strcmp(buffer, "print_debug_file_exp1") == 0) in_print_debug_file_exp1 = 1;
			if(strcmp(buffer, "/print_debug_file_exp1") == 0) in_print_debug_file_exp1 = 0;
			if(strcmp(buffer, "print_debug_file_exp2") == 0) in_print_debug_file_exp2 = 1;
			if(strcmp(buffer, "/print_debug_file_exp2") == 0) in_print_debug_file_exp2 = 0;
			if(strcmp(buffer, "policy_exp1") == 0) in_policy_exp1 = 1;
			if(strcmp(buffer, "/policy_exp1") == 0) in_policy_exp1 = 0;
			if(strcmp(buffer, "print_debug_gov") == 0) in_print_debug_gov = 1;
			if(strcmp(buffer, "/print_debug_gov") == 0) in_print_debug_gov = 0;
			if(strcmp(buffer, "print_debug_household") == 0) in_print_debug_household = 1;
			if(strcmp(buffer, "/print_debug_household") == 0) in_print_debug_household = 0;
			if(strcmp(buffer, "print_debug_credit") == 0) in_print_debug_credit = 1;
			if(strcmp(buffer, "/print_debug_credit") == 0) in_print_debug_credit = 0;
			if(strcmp(buffer, "print_debug_nsa") == 0) in_print_debug_nsa = 1;
			if(strcmp(buffer, "/print_debug_nsa") == 0) in_print_debug_nsa = 0;
			if(strcmp(buffer, "print_debug_consumption") == 0) in_print_debug_consumption = 1;
			if(strcmp(buffer, "/print_debug_consumption") == 0) in_print_debug_consumption = 0;
			if(strcmp(buffer, "print_debug_finman") == 0) in_print_debug_finman = 1;
			if(strcmp(buffer, "/print_debug_finman") == 0) in_print_debug_finman = 0;
			if(strcmp(buffer, "print_debug_production") == 0) in_print_debug_production = 1;
			if(strcmp(buffer, "/print_debug_production") == 0) in_print_debug_production = 0;
			if(strcmp(buffer, "print_debug_mall") == 0) in_print_debug_mall = 1;
			if(strcmp(buffer, "/print_debug_mall") == 0) in_print_debug_mall = 0;
			if(strcmp(buffer, "print_debug") == 0) in_print_debug = 1;
			if(strcmp(buffer, "/print_debug") == 0) in_print_debug = 0;
			if(strcmp(buffer, "print_debug_market_research") == 0) in_print_debug_market_research = 1;
			if(strcmp(buffer, "/print_debug_market_research") == 0) in_print_debug_market_research = 0;
			if(strcmp(buffer, "print_debug_credit_risk_mngt") == 0) in_print_debug_credit_risk_mngt = 1;
			if(strcmp(buffer, "/print_debug_credit_risk_mngt") == 0) in_print_debug_credit_risk_mngt = 0;
			if(strcmp(buffer, "print_debug_credit_unittest") == 0) in_print_debug_credit_unittest = 1;
			if(strcmp(buffer, "/print_debug_credit_unittest") == 0) in_print_debug_credit_unittest = 0;
			if(strcmp(buffer, "print_debug_housing") == 0) in_print_debug_housing = 1;
			if(strcmp(buffer, "/print_debug_housing") == 0) in_print_debug_housing = 0;
			if(strcmp(buffer, "print_debug_housing_unittest") == 0) in_print_debug_housing_unittest = 1;
			if(strcmp(buffer, "/print_debug_housing_unittest") == 0) in_print_debug_housing_unittest = 0;
			if(strcmp(buffer, "print_debug_rental") == 0) in_print_debug_rental = 1;
			if(strcmp(buffer, "/print_debug_rental") == 0) in_print_debug_rental = 0;
			if(strcmp(buffer, "print_debug_rental_unittest") == 0) in_print_debug_rental_unittest = 1;
			if(strcmp(buffer, "/print_debug_rental_unittest") == 0) in_print_debug_rental_unittest = 0;
			if(strcmp(buffer, "switch_behavioral_state_transitions_housing") == 0) in_switch_behavioral_state_transitions_housing = 1;
			if(strcmp(buffer, "/switch_behavioral_state_transitions_housing") == 0) in_switch_behavioral_state_transitions_housing = 0;
			if(strcmp(buffer, "print_debug_mortgage") == 0) in_print_debug_mortgage = 1;
			if(strcmp(buffer, "/print_debug_mortgage") == 0) in_print_debug_mortgage = 0;
			if(strcmp(buffer, "print_debug_mortgage_hh") == 0) in_print_debug_mortgage_hh = 1;
			if(strcmp(buffer, "/print_debug_mortgage_hh") == 0) in_print_debug_mortgage_hh = 0;
			if(strcmp(buffer, "policy_exp_energy_shock") == 0) in_policy_exp_energy_shock = 1;
			if(strcmp(buffer, "/policy_exp_energy_shock") == 0) in_policy_exp_energy_shock = 0;
			if(strcmp(buffer, "policy_exp_stabilization_subsidy") == 0) in_policy_exp_stabilization_subsidy = 1;
			if(strcmp(buffer, "/policy_exp_stabilization_subsidy") == 0) in_policy_exp_stabilization_subsidy = 0;
			if(strcmp(buffer, "policy_exp_stabilization_tax") == 0) in_policy_exp_stabilization_tax = 1;
			if(strcmp(buffer, "/policy_exp_stabilization_tax") == 0) in_policy_exp_stabilization_tax = 0;
			if(strcmp(buffer, "const_bankruptcy_idle_period") == 0) in_const_bankruptcy_idle_period = 1;
			if(strcmp(buffer, "/const_bankruptcy_idle_period") == 0) in_const_bankruptcy_idle_period = 0;
			if(strcmp(buffer, "days_per_month") == 0) in_days_per_month = 1;
			if(strcmp(buffer, "/days_per_month") == 0) in_days_per_month = 0;
			if(strcmp(buffer, "xml_cloned") == 0) in_xml_cloned = 1;
			if(strcmp(buffer, "/xml_cloned") == 0) in_xml_cloned = 0;
			if(strcmp(buffer, "transition_phase_innov") == 0) in_transition_phase_innov = 1;
			if(strcmp(buffer, "/transition_phase_innov") == 0) in_transition_phase_innov = 0;
			if(strcmp(buffer, "transition_phase_recap") == 0) in_transition_phase_recap = 1;
			if(strcmp(buffer, "/transition_phase_recap") == 0) in_transition_phase_recap = 0;
			if(strcmp(buffer, "const_init_transient_period") == 0) in_const_init_transient_period = 1;
			if(strcmp(buffer, "/const_init_transient_period") == 0) in_const_init_transient_period = 0;
			if(strcmp(buffer, "individual_learning") == 0) in_individual_learning = 1;
			if(strcmp(buffer, "/individual_learning") == 0) in_individual_learning = 0;
			if(strcmp(buffer, "const_wage_wealth_ratio") == 0) in_const_wage_wealth_ratio = 1;
			if(strcmp(buffer, "/const_wage_wealth_ratio") == 0) in_const_wage_wealth_ratio = 0;
			if(strcmp(buffer, "const_income_tax_rate") == 0) in_const_income_tax_rate = 1;
			if(strcmp(buffer, "/const_income_tax_rate") == 0) in_const_income_tax_rate = 0;
			if(strcmp(buffer, "gamma_const") == 0) in_gamma_const = 1;
			if(strcmp(buffer, "/gamma_const") == 0) in_gamma_const = 0;
			if(strcmp(buffer, "gamma_quality") == 0) in_gamma_quality = 1;
			if(strcmp(buffer, "/gamma_quality") == 0) in_gamma_quality = 0;
			if(strcmp(buffer, "depreciation_rate") == 0) in_depreciation_rate = 1;
			if(strcmp(buffer, "/depreciation_rate") == 0) in_depreciation_rate = 0;
			if(strcmp(buffer, "discont_rate") == 0) in_discont_rate = 1;
			if(strcmp(buffer, "/discont_rate") == 0) in_discont_rate = 0;
			if(strcmp(buffer, "mark_up") == 0) in_mark_up = 1;
			if(strcmp(buffer, "/mark_up") == 0) in_mark_up = 0;
			if(strcmp(buffer, "lambda") == 0) in_lambda = 1;
			if(strcmp(buffer, "/lambda") == 0) in_lambda = 0;
			if(strcmp(buffer, "target_savings_rate") == 0) in_target_savings_rate = 1;
			if(strcmp(buffer, "/target_savings_rate") == 0) in_target_savings_rate = 0;
			if(strcmp(buffer, "carrol_consumption_parameter") == 0) in_carrol_consumption_parameter = 1;
			if(strcmp(buffer, "/carrol_consumption_parameter") == 0) in_carrol_consumption_parameter = 0;
			if(strcmp(buffer, "quantil_normal_distribution") == 0) in_quantil_normal_distribution = 1;
			if(strcmp(buffer, "/quantil_normal_distribution") == 0) in_quantil_normal_distribution = 0;
			if(strcmp(buffer, "firm_planning_horizon") == 0) in_firm_planning_horizon = 1;
			if(strcmp(buffer, "/firm_planning_horizon") == 0) in_firm_planning_horizon = 0;
			if(strcmp(buffer, "adaption_delivery_volume") == 0) in_adaption_delivery_volume = 1;
			if(strcmp(buffer, "/adaption_delivery_volume") == 0) in_adaption_delivery_volume = 0;
			if(strcmp(buffer, "inv_inertia") == 0) in_inv_inertia = 1;
			if(strcmp(buffer, "/inv_inertia") == 0) in_inv_inertia = 0;
			if(strcmp(buffer, "gamma_logit_vintage_choice") == 0) in_gamma_logit_vintage_choice = 1;
			if(strcmp(buffer, "/gamma_logit_vintage_choice") == 0) in_gamma_logit_vintage_choice = 0;
			if(strcmp(buffer, "delta_logit_vintage_choice") == 0) in_delta_logit_vintage_choice = 1;
			if(strcmp(buffer, "/delta_logit_vintage_choice") == 0) in_delta_logit_vintage_choice = 0;
			if(strcmp(buffer, "housing_alpha") == 0) in_housing_alpha = 1;
			if(strcmp(buffer, "/housing_alpha") == 0) in_housing_alpha = 0;
			if(strcmp(buffer, "housing_beta") == 0) in_housing_beta = 1;
			if(strcmp(buffer, "/housing_beta") == 0) in_housing_beta = 0;
			if(strcmp(buffer, "housing_gamma") == 0) in_housing_gamma = 1;
			if(strcmp(buffer, "/housing_gamma") == 0) in_housing_gamma = 0;
			if(strcmp(buffer, "const_mortgage_initial_risk_of_default") == 0) in_const_mortgage_initial_risk_of_default = 1;
			if(strcmp(buffer, "/const_mortgage_initial_risk_of_default") == 0) in_const_mortgage_initial_risk_of_default = 0;
			if(strcmp(buffer, "const_corporate_initial_risk_of_default") == 0) in_const_corporate_initial_risk_of_default = 1;
			if(strcmp(buffer, "/const_corporate_initial_risk_of_default") == 0) in_const_corporate_initial_risk_of_default = 0;
			if(strcmp(buffer, "max_duration_firm_loans_arrears") == 0) in_max_duration_firm_loans_arrears = 1;
			if(strcmp(buffer, "/max_duration_firm_loans_arrears") == 0) in_max_duration_firm_loans_arrears = 0;
			if(strcmp(buffer, "max_duration_firm_loans_npl") == 0) in_max_duration_firm_loans_npl = 1;
			if(strcmp(buffer, "/max_duration_firm_loans_npl") == 0) in_max_duration_firm_loans_npl = 0;
			if(strcmp(buffer, "max_duration_mortgage_loans_arrears") == 0) in_max_duration_mortgage_loans_arrears = 1;
			if(strcmp(buffer, "/max_duration_mortgage_loans_arrears") == 0) in_max_duration_mortgage_loans_arrears = 0;
			if(strcmp(buffer, "max_duration_mortgage_loans_npl") == 0) in_max_duration_mortgage_loans_npl = 1;
			if(strcmp(buffer, "/max_duration_mortgage_loans_npl") == 0) in_max_duration_mortgage_loans_npl = 0;
			if(strcmp(buffer, "max_dsti_for_repayment") == 0) in_max_dsti_for_repayment = 1;
			if(strcmp(buffer, "/max_dsti_for_repayment") == 0) in_max_dsti_for_repayment = 0;
			if(strcmp(buffer, "max_id") == 0) in_max_id = 1;
			if(strcmp(buffer, "/max_id") == 0) in_max_id = 0;
			if(strcmp(buffer, "number_of_banks_to_apply") == 0) in_number_of_banks_to_apply = 1;
			if(strcmp(buffer, "/number_of_banks_to_apply") == 0) in_number_of_banks_to_apply = 0;
			if(strcmp(buffer, "const_number_of_banks") == 0) in_const_number_of_banks = 1;
			if(strcmp(buffer, "/const_number_of_banks") == 0) in_const_number_of_banks = 0;
			if(strcmp(buffer, "const_installment_periods") == 0) in_const_installment_periods = 1;
			if(strcmp(buffer, "/const_installment_periods") == 0) in_const_installment_periods = 0;
			if(strcmp(buffer, "const_bank_dividend_rate") == 0) in_const_bank_dividend_rate = 1;
			if(strcmp(buffer, "/const_bank_dividend_rate") == 0) in_const_bank_dividend_rate = 0;
			if(strcmp(buffer, "bank_lambda") == 0) in_bank_lambda = 1;
			if(strcmp(buffer, "/bank_lambda") == 0) in_bank_lambda = 0;
			if(strcmp(buffer, "ecb_interest_rate") == 0) in_ecb_interest_rate = 1;
			if(strcmp(buffer, "/ecb_interest_rate") == 0) in_ecb_interest_rate = 0;
			if(strcmp(buffer, "ecb_interest_rate_markdown") == 0) in_ecb_interest_rate_markdown = 1;
			if(strcmp(buffer, "/ecb_interest_rate_markdown") == 0) in_ecb_interest_rate_markdown = 0;
			if(strcmp(buffer, "alfa") == 0) in_alfa = 1;
			if(strcmp(buffer, "/alfa") == 0) in_alfa = 0;
			if(strcmp(buffer, "min_reserve_ratio") == 0) in_min_reserve_ratio = 1;
			if(strcmp(buffer, "/min_reserve_ratio") == 0) in_min_reserve_ratio = 0;
			if(strcmp(buffer, "const_init_pd_corp") == 0) in_const_init_pd_corp = 1;
			if(strcmp(buffer, "/const_init_pd_corp") == 0) in_const_init_pd_corp = 0;
			if(strcmp(buffer, "const_init_lgd_corp") == 0) in_const_init_lgd_corp = 1;
			if(strcmp(buffer, "/const_init_lgd_corp") == 0) in_const_init_lgd_corp = 0;
			if(strcmp(buffer, "const_init_pd_hh") == 0) in_const_init_pd_hh = 1;
			if(strcmp(buffer, "/const_init_pd_hh") == 0) in_const_init_pd_hh = 0;
			if(strcmp(buffer, "const_init_lgd_hh") == 0) in_const_init_lgd_hh = 1;
			if(strcmp(buffer, "/const_init_lgd_hh") == 0) in_const_init_lgd_hh = 0;
			if(strcmp(buffer, "switch_bank_liquidity_full_rationing") == 0) in_switch_bank_liquidity_full_rationing = 1;
			if(strcmp(buffer, "/switch_bank_liquidity_full_rationing") == 0) in_switch_bank_liquidity_full_rationing = 0;
			if(strcmp(buffer, "switch_bank_capital_full_rationing") == 0) in_switch_bank_capital_full_rationing = 1;
			if(strcmp(buffer, "/switch_bank_capital_full_rationing") == 0) in_switch_bank_capital_full_rationing = 0;
			if(strcmp(buffer, "switch_non_risk_weighted_car") == 0) in_switch_non_risk_weighted_car = 1;
			if(strcmp(buffer, "/switch_non_risk_weighted_car") == 0) in_switch_non_risk_weighted_car = 0;
			if(strcmp(buffer, "switch_ban_bank_dividends") == 0) in_switch_ban_bank_dividends = 1;
			if(strcmp(buffer, "/switch_ban_bank_dividends") == 0) in_switch_ban_bank_dividends = 0;
			if(strcmp(buffer, "switch_credit_rationing_unsound_firms") == 0) in_switch_credit_rationing_unsound_firms = 1;
			if(strcmp(buffer, "/switch_credit_rationing_unsound_firms") == 0) in_switch_credit_rationing_unsound_firms = 0;
			if(strcmp(buffer, "switch_credit_rationing_ponzi_firms") == 0) in_switch_credit_rationing_ponzi_firms = 1;
			if(strcmp(buffer, "/switch_credit_rationing_ponzi_firms") == 0) in_switch_credit_rationing_ponzi_firms = 0;
			if(strcmp(buffer, "bank_data_quantile_upper_bound") == 0) in_bank_data_quantile_upper_bound = 1;
			if(strcmp(buffer, "/bank_data_quantile_upper_bound") == 0) in_bank_data_quantile_upper_bound = 0;
			if(strcmp(buffer, "bank_data_quantile_lower_bound") == 0) in_bank_data_quantile_lower_bound = 1;
			if(strcmp(buffer, "/bank_data_quantile_lower_bound") == 0) in_bank_data_quantile_lower_bound = 0;
			if(strcmp(buffer, "const_firm_leverage") == 0) in_const_firm_leverage = 1;
			if(strcmp(buffer, "/const_firm_leverage") == 0) in_const_firm_leverage = 0;
			if(strcmp(buffer, "debt_rescaling_factor") == 0) in_debt_rescaling_factor = 1;
			if(strcmp(buffer, "/debt_rescaling_factor") == 0) in_debt_rescaling_factor = 0;
			if(strcmp(buffer, "target_leverage_ratio") == 0) in_target_leverage_ratio = 1;
			if(strcmp(buffer, "/target_leverage_ratio") == 0) in_target_leverage_ratio = 0;
			if(strcmp(buffer, "target_liquidity_ratio") == 0) in_target_liquidity_ratio = 1;
			if(strcmp(buffer, "/target_liquidity_ratio") == 0) in_target_liquidity_ratio = 0;
			if(strcmp(buffer, "const_dividend_earnings_ratio") == 0) in_const_dividend_earnings_ratio = 1;
			if(strcmp(buffer, "/const_dividend_earnings_ratio") == 0) in_const_dividend_earnings_ratio = 0;
			if(strcmp(buffer, "switch_threshold_full_dividend_rule") == 0) in_switch_threshold_full_dividend_rule = 1;
			if(strcmp(buffer, "/switch_threshold_full_dividend_rule") == 0) in_switch_threshold_full_dividend_rule = 0;
			if(strcmp(buffer, "const_threshold_full_dividend_rule") == 0) in_const_threshold_full_dividend_rule = 1;
			if(strcmp(buffer, "/const_threshold_full_dividend_rule") == 0) in_const_threshold_full_dividend_rule = 0;
			if(strcmp(buffer, "switch_firm_illiquidity_debt_rescaling_rule") == 0) in_switch_firm_illiquidity_debt_rescaling_rule = 1;
			if(strcmp(buffer, "/switch_firm_illiquidity_debt_rescaling_rule") == 0) in_switch_firm_illiquidity_debt_rescaling_rule = 0;
			if(strcmp(buffer, "igfirm_dividend_payout_stretching_month") == 0) in_igfirm_dividend_payout_stretching_month = 1;
			if(strcmp(buffer, "/igfirm_dividend_payout_stretching_month") == 0) in_igfirm_dividend_payout_stretching_month = 0;
			if(strcmp(buffer, "index_price_adj") == 0) in_index_price_adj = 1;
			if(strcmp(buffer, "/index_price_adj") == 0) in_index_price_adj = 0;
			if(strcmp(buffer, "index_price_adj_max") == 0) in_index_price_adj_max = 1;
			if(strcmp(buffer, "/index_price_adj_max") == 0) in_index_price_adj_max = 0;
			if(strcmp(buffer, "index_price_adj_min") == 0) in_index_price_adj_min = 1;
			if(strcmp(buffer, "/index_price_adj_min") == 0) in_index_price_adj_min = 0;
			if(strcmp(buffer, "trading_activity") == 0) in_trading_activity = 1;
			if(strcmp(buffer, "/trading_activity") == 0) in_trading_activity = 0;
			if(strcmp(buffer, "trading_random") == 0) in_trading_random = 1;
			if(strcmp(buffer, "/trading_random") == 0) in_trading_random = 0;
			if(strcmp(buffer, "igfirm_fin_man_debug") == 0) in_igfirm_fin_man_debug = 1;
			if(strcmp(buffer, "/igfirm_fin_man_debug") == 0) in_igfirm_fin_man_debug = 0;
			if(strcmp(buffer, "switch_igfirm_endogenous_innovation_probability") == 0) in_switch_igfirm_endogenous_innovation_probability = 1;
			if(strcmp(buffer, "/switch_igfirm_endogenous_innovation_probability") == 0) in_switch_igfirm_endogenous_innovation_probability = 0;
			if(strcmp(buffer, "igfirm_exogenous_innovation_probability") == 0) in_igfirm_exogenous_innovation_probability = 1;
			if(strcmp(buffer, "/igfirm_exogenous_innovation_probability") == 0) in_igfirm_exogenous_innovation_probability = 0;
			if(strcmp(buffer, "power_of_end_probability_function") == 0) in_power_of_end_probability_function = 1;
			if(strcmp(buffer, "/power_of_end_probability_function") == 0) in_power_of_end_probability_function = 0;
			if(strcmp(buffer, "igfirm_producer_debug") == 0) in_igfirm_producer_debug = 1;
			if(strcmp(buffer, "/igfirm_producer_debug") == 0) in_igfirm_producer_debug = 0;
			if(strcmp(buffer, "igfirm_exogenous_productivity_progress") == 0) in_igfirm_exogenous_productivity_progress = 1;
			if(strcmp(buffer, "/igfirm_exogenous_productivity_progress") == 0) in_igfirm_exogenous_productivity_progress = 0;
			if(strcmp(buffer, "symmetric_shock") == 0) in_symmetric_shock = 1;
			if(strcmp(buffer, "/symmetric_shock") == 0) in_symmetric_shock = 0;
			if(strcmp(buffer, "energy_shock_start") == 0) in_energy_shock_start = 1;
			if(strcmp(buffer, "/energy_shock_start") == 0) in_energy_shock_start = 0;
			if(strcmp(buffer, "energy_shock_end") == 0) in_energy_shock_end = 1;
			if(strcmp(buffer, "/energy_shock_end") == 0) in_energy_shock_end = 0;
			if(strcmp(buffer, "const_energy_shock_intensity") == 0) in_const_energy_shock_intensity = 1;
			if(strcmp(buffer, "/const_energy_shock_intensity") == 0) in_const_energy_shock_intensity = 0;
			if(strcmp(buffer, "energy_shock_frequency") == 0) in_energy_shock_frequency = 1;
			if(strcmp(buffer, "/energy_shock_frequency") == 0) in_energy_shock_frequency = 0;
			if(strcmp(buffer, "innovation_by_random") == 0) in_innovation_by_random = 1;
			if(strcmp(buffer, "/innovation_by_random") == 0) in_innovation_by_random = 0;
			if(strcmp(buffer, "ig_good_limited_offer") == 0) in_ig_good_limited_offer = 1;
			if(strcmp(buffer, "/ig_good_limited_offer") == 0) in_ig_good_limited_offer = 0;
			if(strcmp(buffer, "max_offer_ig_good") == 0) in_max_offer_ig_good = 1;
			if(strcmp(buffer, "/max_offer_ig_good") == 0) in_max_offer_ig_good = 0;
			if(strcmp(buffer, "initial_frontier_firm_transition_phase") == 0) in_initial_frontier_firm_transition_phase = 1;
			if(strcmp(buffer, "/initial_frontier_firm_transition_phase") == 0) in_initial_frontier_firm_transition_phase = 0;
			if(strcmp(buffer, "initial_productivity_firm") == 0) in_initial_productivity_firm = 1;
			if(strcmp(buffer, "/initial_productivity_firm") == 0) in_initial_productivity_firm = 0;
			if(strcmp(buffer, "initial_specific_skills") == 0) in_initial_specific_skills = 1;
			if(strcmp(buffer, "/initial_specific_skills") == 0) in_initial_specific_skills = 0;
			if(strcmp(buffer, "strenght_of_tech_progress") == 0) in_strenght_of_tech_progress = 1;
			if(strcmp(buffer, "/strenght_of_tech_progress") == 0) in_strenght_of_tech_progress = 0;
			if(strcmp(buffer, "linear_combination_pricing_ig_good") == 0) in_linear_combination_pricing_ig_good = 1;
			if(strcmp(buffer, "/linear_combination_pricing_ig_good") == 0) in_linear_combination_pricing_ig_good = 0;
			if(strcmp(buffer, "initial_capital_price_wage_ratio") == 0) in_initial_capital_price_wage_ratio = 1;
			if(strcmp(buffer, "/initial_capital_price_wage_ratio") == 0) in_initial_capital_price_wage_ratio = 0;
			if(strcmp(buffer, "union_strength") == 0) in_union_strength = 1;
			if(strcmp(buffer, "/union_strength") == 0) in_union_strength = 0;
			if(strcmp(buffer, "wage_update") == 0) in_wage_update = 1;
			if(strcmp(buffer, "/wage_update") == 0) in_wage_update = 0;
			if(strcmp(buffer, "min_vacancy") == 0) in_min_vacancy = 1;
			if(strcmp(buffer, "/min_vacancy") == 0) in_min_vacancy = 0;
			if(strcmp(buffer, "wage_reservation_update") == 0) in_wage_reservation_update = 1;
			if(strcmp(buffer, "/wage_reservation_update") == 0) in_wage_reservation_update = 0;
			if(strcmp(buffer, "region_cost") == 0) in_region_cost = 1;
			if(strcmp(buffer, "/region_cost") == 0) in_region_cost = 0;
			if(strcmp(buffer, "delivery_prob_if_critical_stock_0") == 0) in_delivery_prob_if_critical_stock_0 = 1;
			if(strcmp(buffer, "/delivery_prob_if_critical_stock_0") == 0) in_delivery_prob_if_critical_stock_0 = 0;
			if(strcmp(buffer, "number_applications") == 0) in_number_applications = 1;
			if(strcmp(buffer, "/number_applications") == 0) in_number_applications = 0;
			if(strcmp(buffer, "applications_per_day") == 0) in_applications_per_day = 1;
			if(strcmp(buffer, "/applications_per_day") == 0) in_applications_per_day = 0;
			if(strcmp(buffer, "lower_bound_firing") == 0) in_lower_bound_firing = 1;
			if(strcmp(buffer, "/lower_bound_firing") == 0) in_lower_bound_firing = 0;
			if(strcmp(buffer, "upper_bound_firing") == 0) in_upper_bound_firing = 1;
			if(strcmp(buffer, "/upper_bound_firing") == 0) in_upper_bound_firing = 0;
			if(strcmp(buffer, "logit_parameter_specific_skills") == 0) in_logit_parameter_specific_skills = 1;
			if(strcmp(buffer, "/logit_parameter_specific_skills") == 0) in_logit_parameter_specific_skills = 0;
			if(strcmp(buffer, "logit_parameter_general_skills") == 0) in_logit_parameter_general_skills = 1;
			if(strcmp(buffer, "/logit_parameter_general_skills") == 0) in_logit_parameter_general_skills = 0;
			if(strcmp(buffer, "skill_update_acc_to_formula") == 0) in_skill_update_acc_to_formula = 1;
			if(strcmp(buffer, "/skill_update_acc_to_formula") == 0) in_skill_update_acc_to_formula = 0;
			if(strcmp(buffer, "gov_policy_unemployment_benefit_pct") == 0) in_gov_policy_unemployment_benefit_pct = 1;
			if(strcmp(buffer, "/gov_policy_unemployment_benefit_pct") == 0) in_gov_policy_unemployment_benefit_pct = 0;
			if(strcmp(buffer, "gov_policy_money_financing_fraction") == 0) in_gov_policy_money_financing_fraction = 1;
			if(strcmp(buffer, "/gov_policy_money_financing_fraction") == 0) in_gov_policy_money_financing_fraction = 0;
			if(strcmp(buffer, "gov_policy_gdp_fraction_consumption") == 0) in_gov_policy_gdp_fraction_consumption = 1;
			if(strcmp(buffer, "/gov_policy_gdp_fraction_consumption") == 0) in_gov_policy_gdp_fraction_consumption = 0;
			if(strcmp(buffer, "gov_policy_gdp_fraction_investment") == 0) in_gov_policy_gdp_fraction_investment = 1;
			if(strcmp(buffer, "/gov_policy_gdp_fraction_investment") == 0) in_gov_policy_gdp_fraction_investment = 0;
			if(strcmp(buffer, "no_regions_per_gov") == 0) in_no_regions_per_gov = 1;
			if(strcmp(buffer, "/no_regions_per_gov") == 0) in_no_regions_per_gov = 0;
			if(strcmp(buffer, "subsidy_trigger_on") == 0) in_subsidy_trigger_on = 1;
			if(strcmp(buffer, "/subsidy_trigger_on") == 0) in_subsidy_trigger_on = 0;
			if(strcmp(buffer, "subsidy_trigger_off") == 0) in_subsidy_trigger_off = 1;
			if(strcmp(buffer, "/subsidy_trigger_off") == 0) in_subsidy_trigger_off = 0;
			if(strcmp(buffer, "gov_policy_swith_quantitative_easing") == 0) in_gov_policy_swith_quantitative_easing = 1;
			if(strcmp(buffer, "/gov_policy_swith_quantitative_easing") == 0) in_gov_policy_swith_quantitative_easing = 0;
			if(strcmp(buffer, "gov_policy_switch_human_capital_improvement") == 0) in_gov_policy_switch_human_capital_improvement = 1;
			if(strcmp(buffer, "/gov_policy_switch_human_capital_improvement") == 0) in_gov_policy_switch_human_capital_improvement = 0;
			if(strcmp(buffer, "policy_exp_best_technology_subsidy") == 0) in_policy_exp_best_technology_subsidy = 1;
			if(strcmp(buffer, "/policy_exp_best_technology_subsidy") == 0) in_policy_exp_best_technology_subsidy = 0;
			if(strcmp(buffer, "regional_policy_technology_subsidy") == 0) in_regional_policy_technology_subsidy = 1;
			if(strcmp(buffer, "/regional_policy_technology_subsidy") == 0) in_regional_policy_technology_subsidy = 0;
			if(strcmp(buffer, "best_technology_subsidy_pct") == 0) in_best_technology_subsidy_pct = 1;
			if(strcmp(buffer, "/best_technology_subsidy_pct") == 0) in_best_technology_subsidy_pct = 0;
			if(strcmp(buffer, "innovation_switched_on") == 0) in_innovation_switched_on = 1;
			if(strcmp(buffer, "/innovation_switched_on") == 0) in_innovation_switched_on = 0;
			if(strcmp(buffer, "mr_start_price") == 0) in_mr_start_price = 1;
			if(strcmp(buffer, "/mr_start_price") == 0) in_mr_start_price = 0;
			if(strcmp(buffer, "mr_end_price") == 0) in_mr_end_price = 1;
			if(strcmp(buffer, "/mr_end_price") == 0) in_mr_end_price = 0;
			if(strcmp(buffer, "mr_price_increment") == 0) in_mr_price_increment = 1;
			if(strcmp(buffer, "/mr_price_increment") == 0) in_mr_price_increment = 0;
			if(strcmp(buffer, "max_no_employees_product_innovation") == 0) in_max_no_employees_product_innovation = 1;
			if(strcmp(buffer, "/max_no_employees_product_innovation") == 0) in_max_no_employees_product_innovation = 0;
			
			index = 0;
			buffer[index] = '\0';
		}
		else if(c == '<')
		{
			buffer[index] = '\0';
			if(in_environment == 1)
			{
				if(in_rnd_seed == 1) { FLAME_environment_variable_rnd_seed = atoi(buffer); }
				if(in_GSL_RNG_SEED == 1) { FLAME_environment_variable_GSL_RNG_SEED = atof(buffer); }
				if(in_total_regions == 1) { FLAME_environment_variable_total_regions = atoi(buffer); }
				if(in_id_debug_probe == 1) { FLAME_environment_variable_id_debug_probe = atoi(buffer); }
				if(in_print_debug_id_probe == 1) { FLAME_environment_variable_print_debug_id_probe = atoi(buffer); }
				if(in_time_debug_probe == 1) { FLAME_environment_variable_time_debug_probe = atoi(buffer); }
				if(in_print_log == 1) { FLAME_environment_variable_print_log = atoi(buffer); }
				if(in_print_debug_bankruptcy == 1) { FLAME_environment_variable_print_debug_bankruptcy = atoi(buffer); }
				if(in_print_debug_eurostat == 1) { FLAME_environment_variable_print_debug_eurostat = atoi(buffer); }
				if(in_print_debug_ch == 1) { FLAME_environment_variable_print_debug_ch = atoi(buffer); }
				if(in_print_debug_afm == 1) { FLAME_environment_variable_print_debug_afm = atoi(buffer); }
				if(in_print_debug_afm_ch == 1) { FLAME_environment_variable_print_debug_afm_ch = atoi(buffer); }
				if(in_print_debug_exp1 == 1) { FLAME_environment_variable_print_debug_exp1 = atoi(buffer); }
				if(in_print_debug_file_exp1 == 1) { FLAME_environment_variable_print_debug_file_exp1 = atoi(buffer); }
				if(in_print_debug_file_exp2 == 1) { FLAME_environment_variable_print_debug_file_exp2 = atoi(buffer); }
				if(in_policy_exp1 == 1) { FLAME_environment_variable_policy_exp1 = atoi(buffer); }
				if(in_print_debug_gov == 1) { FLAME_environment_variable_print_debug_gov = atoi(buffer); }
				if(in_print_debug_household == 1) { FLAME_environment_variable_print_debug_household = atoi(buffer); }
				if(in_print_debug_credit == 1) { FLAME_environment_variable_print_debug_credit = atoi(buffer); }
				if(in_print_debug_nsa == 1) { FLAME_environment_variable_print_debug_nsa = atoi(buffer); }
				if(in_print_debug_consumption == 1) { FLAME_environment_variable_print_debug_consumption = atoi(buffer); }
				if(in_print_debug_finman == 1) { FLAME_environment_variable_print_debug_finman = atoi(buffer); }
				if(in_print_debug_production == 1) { FLAME_environment_variable_print_debug_production = atoi(buffer); }
				if(in_print_debug_mall == 1) { FLAME_environment_variable_print_debug_mall = atoi(buffer); }
				if(in_print_debug == 1) { FLAME_environment_variable_print_debug = atoi(buffer); }
				if(in_print_debug_market_research == 1) { FLAME_environment_variable_print_debug_market_research = atoi(buffer); }
				if(in_print_debug_credit_risk_mngt == 1) { FLAME_environment_variable_print_debug_credit_risk_mngt = atoi(buffer); }
				if(in_print_debug_credit_unittest == 1) { FLAME_environment_variable_print_debug_credit_unittest = atoi(buffer); }
				if(in_print_debug_housing == 1) { FLAME_environment_variable_print_debug_housing = atoi(buffer); }
				if(in_print_debug_housing_unittest == 1) { FLAME_environment_variable_print_debug_housing_unittest = atoi(buffer); }
				if(in_print_debug_rental == 1) { FLAME_environment_variable_print_debug_rental = atoi(buffer); }
				if(in_print_debug_rental_unittest == 1) { FLAME_environment_variable_print_debug_rental_unittest = atoi(buffer); }
				if(in_switch_behavioral_state_transitions_housing == 1) { FLAME_environment_variable_switch_behavioral_state_transitions_housing = atoi(buffer); }
				if(in_print_debug_mortgage == 1) { FLAME_environment_variable_print_debug_mortgage = atoi(buffer); }
				if(in_print_debug_mortgage_hh == 1) { FLAME_environment_variable_print_debug_mortgage_hh = atoi(buffer); }
				if(in_policy_exp_energy_shock == 1) { FLAME_environment_variable_policy_exp_energy_shock = atoi(buffer); }
				if(in_policy_exp_stabilization_subsidy == 1) { FLAME_environment_variable_policy_exp_stabilization_subsidy = atoi(buffer); }
				if(in_policy_exp_stabilization_tax == 1) { FLAME_environment_variable_policy_exp_stabilization_tax = atoi(buffer); }
				if(in_const_bankruptcy_idle_period == 1) { FLAME_environment_variable_const_bankruptcy_idle_period = atoi(buffer); }
				if(in_days_per_month == 1) { FLAME_environment_variable_days_per_month = atoi(buffer); }
				if(in_xml_cloned == 1) { FLAME_environment_variable_xml_cloned = atoi(buffer); }
				if(in_transition_phase_innov == 1) { FLAME_environment_variable_transition_phase_innov = atoi(buffer); }
				if(in_transition_phase_recap == 1) { FLAME_environment_variable_transition_phase_recap = atoi(buffer); }
				if(in_const_init_transient_period == 1) { FLAME_environment_variable_const_init_transient_period = atoi(buffer); }
				if(in_individual_learning == 1) { FLAME_environment_variable_individual_learning = atoi(buffer); }
				if(in_const_wage_wealth_ratio == 1) { FLAME_environment_variable_const_wage_wealth_ratio = atof(buffer); }
				if(in_const_income_tax_rate == 1) { FLAME_environment_variable_const_income_tax_rate = atof(buffer); }
				if(in_gamma_const == 1) { FLAME_environment_variable_gamma_const = atof(buffer); }
				if(in_gamma_quality == 1) { FLAME_environment_variable_gamma_quality = atof(buffer); }
				if(in_depreciation_rate == 1) { FLAME_environment_variable_depreciation_rate = atof(buffer); }
				if(in_discont_rate == 1) { FLAME_environment_variable_discont_rate = atof(buffer); }
				if(in_mark_up == 1) { FLAME_environment_variable_mark_up = atof(buffer); }
				if(in_lambda == 1) { FLAME_environment_variable_lambda = atof(buffer); }
				if(in_target_savings_rate == 1) { FLAME_environment_variable_target_savings_rate = atof(buffer); }
				if(in_carrol_consumption_parameter == 1) { FLAME_environment_variable_carrol_consumption_parameter = atof(buffer); }
				if(in_quantil_normal_distribution == 1) { FLAME_environment_variable_quantil_normal_distribution = atof(buffer); }
				if(in_firm_planning_horizon == 1) { FLAME_environment_variable_firm_planning_horizon = atoi(buffer); }
				if(in_adaption_delivery_volume == 1) { FLAME_environment_variable_adaption_delivery_volume = atof(buffer); }
				if(in_inv_inertia == 1) { FLAME_environment_variable_inv_inertia = atof(buffer); }
				if(in_gamma_logit_vintage_choice == 1) { FLAME_environment_variable_gamma_logit_vintage_choice = atof(buffer); }
				if(in_delta_logit_vintage_choice == 1) { FLAME_environment_variable_delta_logit_vintage_choice = atof(buffer); }
				if(in_housing_alpha == 1) { FLAME_environment_variable_housing_alpha = atof(buffer); }
				if(in_housing_beta == 1) { FLAME_environment_variable_housing_beta = atof(buffer); }
				if(in_housing_gamma == 1) { FLAME_environment_variable_housing_gamma = atof(buffer); }
				if(in_const_mortgage_initial_risk_of_default == 1) { FLAME_environment_variable_const_mortgage_initial_risk_of_default = atof(buffer); }
				if(in_const_corporate_initial_risk_of_default == 1) { FLAME_environment_variable_const_corporate_initial_risk_of_default = atof(buffer); }
				if(in_max_duration_firm_loans_arrears == 1) { FLAME_environment_variable_max_duration_firm_loans_arrears = atoi(buffer); }
				if(in_max_duration_firm_loans_npl == 1) { FLAME_environment_variable_max_duration_firm_loans_npl = atoi(buffer); }
				if(in_max_duration_mortgage_loans_arrears == 1) { FLAME_environment_variable_max_duration_mortgage_loans_arrears = atoi(buffer); }
				if(in_max_duration_mortgage_loans_npl == 1) { FLAME_environment_variable_max_duration_mortgage_loans_npl = atoi(buffer); }
				if(in_max_dsti_for_repayment == 1) { FLAME_environment_variable_max_dsti_for_repayment = atof(buffer); }
				if(in_max_id == 1) { FLAME_environment_variable_max_id = atoi(buffer); }
				if(in_number_of_banks_to_apply == 1) { FLAME_environment_variable_number_of_banks_to_apply = atoi(buffer); }
				if(in_const_number_of_banks == 1) { FLAME_environment_variable_const_number_of_banks = atoi(buffer); }
				if(in_const_installment_periods == 1) { FLAME_environment_variable_const_installment_periods = atoi(buffer); }
				if(in_const_bank_dividend_rate == 1) { FLAME_environment_variable_const_bank_dividend_rate = atof(buffer); }
				if(in_bank_lambda == 1) { FLAME_environment_variable_bank_lambda = atof(buffer); }
				if(in_ecb_interest_rate == 1) { FLAME_environment_variable_ecb_interest_rate = atof(buffer); }
				if(in_ecb_interest_rate_markdown == 1) { FLAME_environment_variable_ecb_interest_rate_markdown = atof(buffer); }
				if(in_alfa == 1) { FLAME_environment_variable_alfa = atof(buffer); }
				if(in_min_reserve_ratio == 1) { FLAME_environment_variable_min_reserve_ratio = atof(buffer); }
				if(in_const_init_pd_corp == 1) { FLAME_environment_variable_const_init_pd_corp = atof(buffer); }
				if(in_const_init_lgd_corp == 1) { FLAME_environment_variable_const_init_lgd_corp = atof(buffer); }
				if(in_const_init_pd_hh == 1) { FLAME_environment_variable_const_init_pd_hh = atof(buffer); }
				if(in_const_init_lgd_hh == 1) { FLAME_environment_variable_const_init_lgd_hh = atof(buffer); }
				if(in_switch_bank_liquidity_full_rationing == 1) { FLAME_environment_variable_switch_bank_liquidity_full_rationing = atoi(buffer); }
				if(in_switch_bank_capital_full_rationing == 1) { FLAME_environment_variable_switch_bank_capital_full_rationing = atoi(buffer); }
				if(in_switch_non_risk_weighted_car == 1) { FLAME_environment_variable_switch_non_risk_weighted_car = atoi(buffer); }
				if(in_switch_ban_bank_dividends == 1) { FLAME_environment_variable_switch_ban_bank_dividends = atoi(buffer); }
				if(in_switch_credit_rationing_unsound_firms == 1) { FLAME_environment_variable_switch_credit_rationing_unsound_firms = atoi(buffer); }
				if(in_switch_credit_rationing_ponzi_firms == 1) { FLAME_environment_variable_switch_credit_rationing_ponzi_firms = atoi(buffer); }
				if(in_bank_data_quantile_upper_bound == 1) { FLAME_environment_variable_bank_data_quantile_upper_bound = atof(buffer); }
				if(in_bank_data_quantile_lower_bound == 1) { FLAME_environment_variable_bank_data_quantile_lower_bound = atof(buffer); }
				if(in_const_firm_leverage == 1) { FLAME_environment_variable_const_firm_leverage = atof(buffer); }
				if(in_debt_rescaling_factor == 1) { FLAME_environment_variable_debt_rescaling_factor = atof(buffer); }
				if(in_target_leverage_ratio == 1) { FLAME_environment_variable_target_leverage_ratio = atof(buffer); }
				if(in_target_liquidity_ratio == 1) { FLAME_environment_variable_target_liquidity_ratio = atof(buffer); }
				if(in_const_dividend_earnings_ratio == 1) { FLAME_environment_variable_const_dividend_earnings_ratio = atof(buffer); }
				if(in_switch_threshold_full_dividend_rule == 1) { FLAME_environment_variable_switch_threshold_full_dividend_rule = atoi(buffer); }
				if(in_const_threshold_full_dividend_rule == 1) { FLAME_environment_variable_const_threshold_full_dividend_rule = atof(buffer); }
				if(in_switch_firm_illiquidity_debt_rescaling_rule == 1) { FLAME_environment_variable_switch_firm_illiquidity_debt_rescaling_rule = atoi(buffer); }
				if(in_igfirm_dividend_payout_stretching_month == 1) { FLAME_environment_variable_igfirm_dividend_payout_stretching_month = atoi(buffer); }
				if(in_index_price_adj == 1) { FLAME_environment_variable_index_price_adj = atof(buffer); }
				if(in_index_price_adj_max == 1) { FLAME_environment_variable_index_price_adj_max = atof(buffer); }
				if(in_index_price_adj_min == 1) { FLAME_environment_variable_index_price_adj_min = atof(buffer); }
				if(in_trading_activity == 1) { FLAME_environment_variable_trading_activity = atoi(buffer); }
				if(in_trading_random == 1) { FLAME_environment_variable_trading_random = atoi(buffer); }
				if(in_igfirm_fin_man_debug == 1) { FLAME_environment_variable_igfirm_fin_man_debug = atoi(buffer); }
				if(in_switch_igfirm_endogenous_innovation_probability == 1) { FLAME_environment_variable_switch_igfirm_endogenous_innovation_probability = atoi(buffer); }
				if(in_igfirm_exogenous_innovation_probability == 1) { FLAME_environment_variable_igfirm_exogenous_innovation_probability = atof(buffer); }
				if(in_power_of_end_probability_function == 1) { FLAME_environment_variable_power_of_end_probability_function = atof(buffer); }
				if(in_igfirm_producer_debug == 1) { FLAME_environment_variable_igfirm_producer_debug = atoi(buffer); }
				if(in_igfirm_exogenous_productivity_progress == 1) { FLAME_environment_variable_igfirm_exogenous_productivity_progress = atof(buffer); }
				if(in_symmetric_shock == 1) { FLAME_environment_variable_symmetric_shock = atoi(buffer); }
				if(in_energy_shock_start == 1) { FLAME_environment_variable_energy_shock_start = atoi(buffer); }
				if(in_energy_shock_end == 1) { FLAME_environment_variable_energy_shock_end = atoi(buffer); }
				if(in_const_energy_shock_intensity == 1) { FLAME_environment_variable_const_energy_shock_intensity = atof(buffer); }
				if(in_energy_shock_frequency == 1) { FLAME_environment_variable_energy_shock_frequency = atoi(buffer); }
				if(in_innovation_by_random == 1) { FLAME_environment_variable_innovation_by_random = atoi(buffer); }
				if(in_ig_good_limited_offer == 1) { FLAME_environment_variable_ig_good_limited_offer = atoi(buffer); }
				if(in_max_offer_ig_good == 1) { FLAME_environment_variable_max_offer_ig_good = atoi(buffer); }
				if(in_initial_frontier_firm_transition_phase == 1) { FLAME_environment_variable_initial_frontier_firm_transition_phase = atof(buffer); }
				if(in_initial_productivity_firm == 1) { FLAME_environment_variable_initial_productivity_firm = atof(buffer); }
				if(in_initial_specific_skills == 1) { FLAME_environment_variable_initial_specific_skills = atof(buffer); }
				if(in_strenght_of_tech_progress == 1) { FLAME_environment_variable_strenght_of_tech_progress = atoi(buffer); }
				if(in_linear_combination_pricing_ig_good == 1) { FLAME_environment_variable_linear_combination_pricing_ig_good = atof(buffer); }
				if(in_initial_capital_price_wage_ratio == 1) { FLAME_environment_variable_initial_capital_price_wage_ratio = atof(buffer); }
				if(in_union_strength == 1) { FLAME_environment_variable_union_strength = atof(buffer); }
				if(in_wage_update == 1) { FLAME_environment_variable_wage_update = atof(buffer); }
				if(in_min_vacancy == 1) { FLAME_environment_variable_min_vacancy = atoi(buffer); }
				if(in_wage_reservation_update == 1) { FLAME_environment_variable_wage_reservation_update = atof(buffer); }
				if(in_region_cost == 1) { FLAME_environment_variable_region_cost = atof(buffer); }
				if(in_delivery_prob_if_critical_stock_0 == 1) { FLAME_environment_variable_delivery_prob_if_critical_stock_0 = atof(buffer); }
				if(in_number_applications == 1) { FLAME_environment_variable_number_applications = atoi(buffer); }
				if(in_applications_per_day == 1) { FLAME_environment_variable_applications_per_day = atoi(buffer); }
				if(in_lower_bound_firing == 1) { FLAME_environment_variable_lower_bound_firing = atoi(buffer); }
				if(in_upper_bound_firing == 1) { FLAME_environment_variable_upper_bound_firing = atoi(buffer); }
				if(in_logit_parameter_specific_skills == 1) { FLAME_environment_variable_logit_parameter_specific_skills = atof(buffer); }
				if(in_logit_parameter_general_skills == 1) { FLAME_environment_variable_logit_parameter_general_skills = atof(buffer); }
				if(in_skill_update_acc_to_formula == 1) { FLAME_environment_variable_skill_update_acc_to_formula = atoi(buffer); }
				if(in_gov_policy_unemployment_benefit_pct == 1) { FLAME_environment_variable_gov_policy_unemployment_benefit_pct = atof(buffer); }
				if(in_gov_policy_money_financing_fraction == 1) { FLAME_environment_variable_gov_policy_money_financing_fraction = atof(buffer); }
				if(in_gov_policy_gdp_fraction_consumption == 1) { FLAME_environment_variable_gov_policy_gdp_fraction_consumption = atof(buffer); }
				if(in_gov_policy_gdp_fraction_investment == 1) { FLAME_environment_variable_gov_policy_gdp_fraction_investment = atof(buffer); }
				if(in_no_regions_per_gov == 1) { FLAME_environment_variable_no_regions_per_gov = atoi(buffer); }
				if(in_subsidy_trigger_on == 1) { FLAME_environment_variable_subsidy_trigger_on = atof(buffer); }
				if(in_subsidy_trigger_off == 1) { FLAME_environment_variable_subsidy_trigger_off = atof(buffer); }
				if(in_gov_policy_swith_quantitative_easing == 1) { FLAME_environment_variable_gov_policy_swith_quantitative_easing = atoi(buffer); }
				if(in_gov_policy_switch_human_capital_improvement == 1) { FLAME_environment_variable_gov_policy_switch_human_capital_improvement = atoi(buffer); }
				if(in_policy_exp_best_technology_subsidy == 1) { FLAME_environment_variable_policy_exp_best_technology_subsidy = atoi(buffer); }
				if(in_regional_policy_technology_subsidy == 1) { FLAME_environment_variable_regional_policy_technology_subsidy = atoi(buffer); }
				if(in_best_technology_subsidy_pct == 1) { FLAME_environment_variable_best_technology_subsidy_pct = atof(buffer); }
				if(in_innovation_switched_on == 1) { FLAME_environment_variable_innovation_switched_on = atoi(buffer); }
				if(in_mr_start_price == 1) { FLAME_environment_variable_mr_start_price = atof(buffer); }
				if(in_mr_end_price == 1) { FLAME_environment_variable_mr_end_price = atof(buffer); }
				if(in_mr_price_increment == 1) { FLAME_environment_variable_mr_price_increment = atof(buffer); }
				if(in_max_no_employees_product_innovation == 1) { FLAME_environment_variable_max_no_employees_product_innovation = atoi(buffer); }
				
			}
			index = 0;
			buffer[index] = '\0';
		}
		else
		{
			buffer[index] = c;
			if(index < 999) index++;
		}
	}
	/* Close file */
	(void)fclose(file);

	return 0;
}

int readAgentXML(char * location,
				double cloud_data[],
				int partition_method,
				int flag,
				int number_partitions,
				int agent_count,
				int * itno)
{
	FILE * file;
	char c = '\0';
	char buffer[100000];
	char agentname[10000];
	int index = 0;
	int j; /* Index for reading arrays */
	int rc;
	int in_itno = 0;
	int FLAME_in_xagent = 0;
	int FLAME_in_name = 0;
	int in_Firm_agent = 0;
	int in_Eurostat_agent = 0;
	
	int in_id = 0;
	
	xmachine_memory_Firm * current_Firm_agent = NULL;
	xmachine_memory_Eurostat * current_Eurostat_agent = NULL;
	
	/* Things for round-robin partitioning */
	int geometric = 1;
	int other = 2;
	double posx=0.0, posy=0.0, posz=0.0;

	j = 0;
	rc = 0;
	
	/* Use j and rc to stop compiler warnings if not used */
	if(j == 0 && rc == 0) {}
	
	agentname[0] = '\0';
	buffer[0] = '\0';

	/* Open file */
	if((file = fopen(location, "r"))==NULL)
	{
		printf("Error: cannot open import xml file '%s'\n", location);
		exit(0);
	}
	printf("Reading agent data from: %s\n", location);
	/* Keep reading file until EOF */
	while(c != (char)EOF)
	{
		/* Get the next char from the file */
		c = (char)fgetc(file);
		if(c == '>')
		{
			buffer[index] = '\0';
			if(strcmp(buffer, "itno") == 0) in_itno = 1;
			if(strcmp(buffer, "/itno") == 0) in_itno = 0;
			if(strcmp(buffer, "xagent") == 0)
			{
				FLAME_in_xagent = 1;
				agentname[0] = '\0';
			}
			if(strcmp(buffer, "/xagent") == 0)
			{	
				if(strcmp(agentname, "Firm") == 0)
				{
					if(current_Firm_agent == NULL) { printf("Memory error reading Firm agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_Firm_agent_internal(current_Firm_agent, Firm_start_Firm_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_Firm_agent_internal(current_Firm_agent, Firm_start_Firm_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_Firm_agent_internal(current_Firm_agent, Firm_start_Firm_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "Household") == 0)
				{
					if(current_Household_agent == NULL) { printf("Memory error reading Household agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_Household_agent_internal(current_Household_agent, Household_start_Household_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_Household_agent_internal(current_Household_agent, Household_start_Household_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_Household_agent_internal(current_Household_agent, Household_start_Household_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "Mall") == 0)
				{
					if(current_Mall_agent == NULL) { printf("Memory error reading Mall agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_Mall_agent_internal(current_Mall_agent, Mall_start_Mall_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_Mall_agent_internal(current_Mall_agent, Mall_start_Mall_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_Mall_agent_internal(current_Mall_agent, Mall_start_Mall_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "IGFirm") == 0)
				{
					if(current_IGFirm_agent == NULL) { printf("Memory error reading IGFirm agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_IGFirm_agent_internal(current_IGFirm_agent, IGFirm_IGFirm_start_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_IGFirm_agent_internal(current_IGFirm_agent, IGFirm_IGFirm_start_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_IGFirm_agent_internal(current_IGFirm_agent, IGFirm_IGFirm_start_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "Eurostat") == 0)
				{
					if(current_Eurostat_agent == NULL) { printf("Memory error reading Eurostat agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_Eurostat_agent_internal(current_Eurostat_agent, Eurostat_start_Eurostat_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_Eurostat_agent_internal(current_Eurostat_agent, Eurostat_start_Eurostat_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_Eurostat_agent_internal(current_Eurostat_agent, Eurostat_start_Eurostat_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "Bank") == 0)
				{
					if(current_Bank_agent == NULL) { printf("Memory error reading Bank agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_Bank_agent_internal(current_Bank_agent, Bank_start_Bank_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_Bank_agent_internal(current_Bank_agent, Bank_start_Bank_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_Bank_agent_internal(current_Bank_agent, Bank_start_Bank_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "Government") == 0)
				{
					if(current_Government_agent == NULL) { printf("Memory error reading Government agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_Government_agent_internal(current_Government_agent, Government_start_Government_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_Government_agent_internal(current_Government_agent, Government_start_Government_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_Government_agent_internal(current_Government_agent, Government_start_Government_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "CentralBank") == 0)
				{
					if(current_CentralBank_agent == NULL) { printf("Memory error reading CentralBank agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_CentralBank_agent_internal(current_CentralBank_agent, CentralBank_start_Central_Bank_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_CentralBank_agent_internal(current_CentralBank_agent, CentralBank_start_Central_Bank_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_CentralBank_agent_internal(current_CentralBank_agent, CentralBank_start_Central_Bank_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "ClearingHouse") == 0)
				{
					if(current_ClearingHouse_agent == NULL) { printf("Memory error reading ClearingHouse agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_ClearingHouse_agent_internal(current_ClearingHouse_agent, ClearingHouse_start_ClearingHouse_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_ClearingHouse_agent_internal(current_ClearingHouse_agent, ClearingHouse_start_ClearingHouse_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_ClearingHouse_agent_internal(current_ClearingHouse_agent, ClearingHouse_start_ClearingHouse_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "NSA") == 0)
				{
					if(current_NSA_agent == NULL) { printf("Memory error reading NSA agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_NSA_agent_internal(current_NSA_agent, NSA_start_NSA_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_NSA_agent_internal(current_NSA_agent, NSA_start_NSA_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_NSA_agent_internal(current_NSA_agent, NSA_start_NSA_state);
							}
							++agent_count;
						}
					}
				}
				else
				{
					printf("Warning: agent name undefined - '%s'\n", agentname);
					exit(0);
				}
				agentname[0] = '\0';
				FLAME_in_xagent = 0;
				in_Firm_agent = 0;
				in_Household_agent = 0;
				in_Mall_agent = 0;
				in_IGFirm_agent = 0;
				in_Eurostat_agent = 0;
				in_Bank_agent = 0;
				in_Government_agent = 0;
				in_CentralBank_agent = 0;
				in_ClearingHouse_agent = 0;
				in_NSA_agent = 0;
				
			}
			if(strcmp(buffer, "name") == 0) FLAME_in_name = 1;
			if(strcmp(buffer, "/name") == 0) FLAME_in_name = 0;
			if(strcmp(buffer, "id") == 0) { in_id = 1; }
			if(strcmp(buffer, "/id") == 0) { in_id = 0; }
			if(strcmp(buffer, "region_id") == 0) { in_region_id = 1; }
			if(strcmp(buffer, "/region_id") == 0) { in_region_id = 0; }
			if(strcmp(buffer, "gov_id") == 0) { in_gov_id = 1; }
			if(strcmp(buffer, "/gov_id") == 0) { in_gov_id = 0; }
			if(strcmp(buffer, "day_of_month_to_act") == 0) { in_day_of_month_to_act = 1; }
			if(strcmp(buffer, "/day_of_month_to_act") == 0) { in_day_of_month_to_act = 0; }
			if(strcmp(buffer, "last_day_of_month_to_act") == 0) { in_last_day_of_month_to_act = 1; }
			if(strcmp(buffer, "/last_day_of_month_to_act") == 0) { in_last_day_of_month_to_act = 0; }
			if(strcmp(buffer, "payment_account") == 0) { in_payment_account = 1; }
			if(strcmp(buffer, "/payment_account") == 0) { in_payment_account = 0; }
			if(strcmp(buffer, "payment_account_balance_sheet") == 0) { in_payment_account_balance_sheet = 1; }
			if(strcmp(buffer, "/payment_account_balance_sheet") == 0) { in_payment_account_balance_sheet = 0; }
			if(strcmp(buffer, "bank_id") == 0) { in_bank_id = 1; }
			if(strcmp(buffer, "/bank_id") == 0) { in_bank_id = 0; }
			if(strcmp(buffer, "partition_id") == 0) { in_partition_id = 1; }
			if(strcmp(buffer, "/partition_id") == 0) { in_partition_id = 0; }
			if(strcmp(buffer, "init_transient_period") == 0) { in_init_transient_period = 1; }
			if(strcmp(buffer, "/init_transient_period") == 0) { in_init_transient_period = 0; }
			if(strcmp(buffer, "cpi") == 0) { in_cpi = 1; }
			if(strcmp(buffer, "/cpi") == 0) { in_cpi = 0; }
			if(strcmp(buffer, "mean_wage") == 0) { in_mean_wage = 1; }
			if(strcmp(buffer, "/mean_wage") == 0) { in_mean_wage = 0; }
			if(strcmp(buffer, "total_mean_wage") == 0) { in_total_mean_wage = 1; }
			if(strcmp(buffer, "/total_mean_wage") == 0) { in_total_mean_wage = 0; }
			if(strcmp(buffer, "mean_wage_r_and_d") == 0) { in_mean_wage_r_and_d = 1; }
			if(strcmp(buffer, "/mean_wage_r_and_d") == 0) { in_mean_wage_r_and_d = 0; }
			if(strcmp(buffer, "needed_capital_stock") == 0) { in_needed_capital_stock = 1; }
			if(strcmp(buffer, "/needed_capital_stock") == 0) { in_needed_capital_stock = 0; }
			if(strcmp(buffer, "stock") == 0) { in_stock = 1; }
			if(strcmp(buffer, "/stock") == 0) { in_stock = 0; }
			if(strcmp(buffer, "critical_stock") == 0) { in_critical_stock = 1; }
			if(strcmp(buffer, "/critical_stock") == 0) { in_critical_stock = 0; }
			if(strcmp(buffer, "actual_cap_price") == 0) { in_actual_cap_price = 1; }
			if(strcmp(buffer, "/actual_cap_price") == 0) { in_actual_cap_price = 0; }
			if(strcmp(buffer, "mean_specific_skills") == 0) { in_mean_specific_skills = 1; }
			if(strcmp(buffer, "/mean_specific_skills") == 0) { in_mean_specific_skills = 0; }
			if(strcmp(buffer, "planned_production_quantity") == 0) { in_planned_production_quantity = 1; }
			if(strcmp(buffer, "/planned_production_quantity") == 0) { in_planned_production_quantity = 0; }
			if(strcmp(buffer, "production_quantity") == 0) { in_production_quantity = 1; }
			if(strcmp(buffer, "/production_quantity") == 0) { in_production_quantity = 0; }
			if(strcmp(buffer, "planned_output") == 0) { in_planned_output = 1; }
			if(strcmp(buffer, "/planned_output") == 0) { in_planned_output = 0; }
			if(strcmp(buffer, "output") == 0) { in_output = 1; }
			if(strcmp(buffer, "/output") == 0) { in_output = 0; }
			if(strcmp(buffer, "unit_costs") == 0) { in_unit_costs = 1; }
			if(strcmp(buffer, "/unit_costs") == 0) { in_unit_costs = 0; }
			if(strcmp(buffer, "total_supply") == 0) { in_total_supply = 1; }
			if(strcmp(buffer, "/total_supply") == 0) { in_total_supply = 0; }
			if(strcmp(buffer, "production_costs") == 0) { in_production_costs = 1; }
			if(strcmp(buffer, "/production_costs") == 0) { in_production_costs = 0; }
			if(strcmp(buffer, "total_buffer") == 0) { in_total_buffer = 1; }
			if(strcmp(buffer, "/total_buffer") == 0) { in_total_buffer = 0; }
			if(strcmp(buffer, "revenue_per_day") == 0) { in_revenue_per_day = 1; }
			if(strcmp(buffer, "/revenue_per_day") == 0) { in_revenue_per_day = 0; }
			if(strcmp(buffer, "technological_frontier") == 0) { in_technological_frontier = 1; }
			if(strcmp(buffer, "/technological_frontier") == 0) { in_technological_frontier = 0; }
			if(strcmp(buffer, "technology_vintages") == 0) { in_technology_vintages = 1; }
			if(strcmp(buffer, "/technology_vintages") == 0) { in_technology_vintages = 0; }
			if(strcmp(buffer, "vintage_selected") == 0) { in_vintage_selected = 1; }
			if(strcmp(buffer, "/vintage_selected") == 0) { in_vintage_selected = 0; }
			if(strcmp(buffer, "initial_technology") == 0) { in_initial_technology = 1; }
			if(strcmp(buffer, "/initial_technology") == 0) { in_initial_technology = 0; }
			if(strcmp(buffer, "utilization_capacity") == 0) { in_utilization_capacity = 1; }
			if(strcmp(buffer, "/utilization_capacity") == 0) { in_utilization_capacity = 0; }
			if(strcmp(buffer, "cum_revenue") == 0) { in_cum_revenue = 1; }
			if(strcmp(buffer, "/cum_revenue") == 0) { in_cum_revenue = 0; }
			if(strcmp(buffer, "malls_sales_statistics") == 0) { in_malls_sales_statistics = 1; }
			if(strcmp(buffer, "/malls_sales_statistics") == 0) { in_malls_sales_statistics = 0; }
			if(strcmp(buffer, "quality") == 0) { in_quality = 1; }
			if(strcmp(buffer, "/quality") == 0) { in_quality = 0; }
			if(strcmp(buffer, "price") == 0) { in_price = 1; }
			if(strcmp(buffer, "/price") == 0) { in_price = 0; }
			if(strcmp(buffer, "price_last_month") == 0) { in_price_last_month = 1; }
			if(strcmp(buffer, "/price_last_month") == 0) { in_price_last_month = 0; }
			if(strcmp(buffer, "actual_mark_up") == 0) { in_actual_mark_up = 1; }
			if(strcmp(buffer, "/actual_mark_up") == 0) { in_actual_mark_up = 0; }
			if(strcmp(buffer, "demand_capital_stock") == 0) { in_demand_capital_stock = 1; }
			if(strcmp(buffer, "/demand_capital_stock") == 0) { in_demand_capital_stock = 0; }
			if(strcmp(buffer, "effective_investments") == 0) { in_effective_investments = 1; }
			if(strcmp(buffer, "/effective_investments") == 0) { in_effective_investments = 0; }
			if(strcmp(buffer, "effective_capital_stock") == 0) { in_effective_capital_stock = 1; }
			if(strcmp(buffer, "/effective_capital_stock") == 0) { in_effective_capital_stock = 0; }
			if(strcmp(buffer, "planned_production_costs") == 0) { in_planned_production_costs = 1; }
			if(strcmp(buffer, "/planned_production_costs") == 0) { in_planned_production_costs = 0; }
			if(strcmp(buffer, "labour_costs_production") == 0) { in_labour_costs_production = 1; }
			if(strcmp(buffer, "/labour_costs_production") == 0) { in_labour_costs_production = 0; }
			if(strcmp(buffer, "labour_costs_innovation") == 0) { in_labour_costs_innovation = 1; }
			if(strcmp(buffer, "/labour_costs_innovation") == 0) { in_labour_costs_innovation = 0; }
			if(strcmp(buffer, "intermediate_quality_level_developing") == 0) { in_intermediate_quality_level_developing = 1; }
			if(strcmp(buffer, "/intermediate_quality_level_developing") == 0) { in_intermediate_quality_level_developing = 0; }
			if(strcmp(buffer, "adaption_production_volume_due_to_insufficient_finances") == 0) { in_adaption_production_volume_due_to_insufficient_finances = 1; }
			if(strcmp(buffer, "/adaption_production_volume_due_to_insufficient_finances") == 0) { in_adaption_production_volume_due_to_insufficient_finances = 0; }
			if(strcmp(buffer, "sold_quantities") == 0) { in_sold_quantities = 1; }
			if(strcmp(buffer, "/sold_quantities") == 0) { in_sold_quantities = 0; }
			if(strcmp(buffer, "total_sold_quantity") == 0) { in_total_sold_quantity = 1; }
			if(strcmp(buffer, "/total_sold_quantity") == 0) { in_total_sold_quantity = 0; }
			if(strcmp(buffer, "cum_total_sold_quantity") == 0) { in_cum_total_sold_quantity = 1; }
			if(strcmp(buffer, "/cum_total_sold_quantity") == 0) { in_cum_total_sold_quantity = 0; }
			if(strcmp(buffer, "sold_quantity_in_calendar_month") == 0) { in_sold_quantity_in_calendar_month = 1; }
			if(strcmp(buffer, "/sold_quantity_in_calendar_month") == 0) { in_sold_quantity_in_calendar_month = 0; }
			if(strcmp(buffer, "delivery_volume") == 0) { in_delivery_volume = 1; }
			if(strcmp(buffer, "/delivery_volume") == 0) { in_delivery_volume = 0; }
			if(strcmp(buffer, "planned_delivery_volume") == 0) { in_planned_delivery_volume = 1; }
			if(strcmp(buffer, "/planned_delivery_volume") == 0) { in_planned_delivery_volume = 0; }
			if(strcmp(buffer, "current_mall_stocks") == 0) { in_current_mall_stocks = 1; }
			if(strcmp(buffer, "/current_mall_stocks") == 0) { in_current_mall_stocks = 0; }
			if(strcmp(buffer, "last_planned_production_quantities") == 0) { in_last_planned_production_quantities = 1; }
			if(strcmp(buffer, "/last_planned_production_quantities") == 0) { in_last_planned_production_quantities = 0; }
			if(strcmp(buffer, "total_external_financing_obtained") == 0) { in_total_external_financing_obtained = 1; }
			if(strcmp(buffer, "/total_external_financing_obtained") == 0) { in_total_external_financing_obtained = 0; }
			if(strcmp(buffer, "capital_costs") == 0) { in_capital_costs = 1; }
			if(strcmp(buffer, "/capital_costs") == 0) { in_capital_costs = 0; }
			if(strcmp(buffer, "employees_needed_production") == 0) { in_employees_needed_production = 1; }
			if(strcmp(buffer, "/employees_needed_production") == 0) { in_employees_needed_production = 0; }
			if(strcmp(buffer, "no_employees_production") == 0) { in_no_employees_production = 1; }
			if(strcmp(buffer, "/no_employees_production") == 0) { in_no_employees_production = 0; }
			if(strcmp(buffer, "planned_innovation_expenditures") == 0) { in_planned_innovation_expenditures = 1; }
			if(strcmp(buffer, "/planned_innovation_expenditures") == 0) { in_planned_innovation_expenditures = 0; }
			if(strcmp(buffer, "planned_expenditures_production_innovation") == 0) { in_planned_expenditures_production_innovation = 1; }
			if(strcmp(buffer, "/planned_expenditures_production_innovation") == 0) { in_planned_expenditures_production_innovation = 0; }
			if(strcmp(buffer, "labour_costs") == 0) { in_labour_costs = 1; }
			if(strcmp(buffer, "/labour_costs") == 0) { in_labour_costs = 0; }
			if(strcmp(buffer, "capital_stock_vintages") == 0) { in_capital_stock_vintages = 1; }
			if(strcmp(buffer, "/capital_stock_vintages") == 0) { in_capital_stock_vintages = 0; }
			if(strcmp(buffer, "vintage_choice_taken") == 0) { in_vintage_choice_taken = 1; }
			if(strcmp(buffer, "/vintage_choice_taken") == 0) { in_vintage_choice_taken = 0; }
			if(strcmp(buffer, "capital_financing") == 0) { in_capital_financing = 1; }
			if(strcmp(buffer, "/capital_financing") == 0) { in_capital_financing = 0; }
			if(strcmp(buffer, "financial_resources_for_production") == 0) { in_financial_resources_for_production = 1; }
			if(strcmp(buffer, "/financial_resources_for_production") == 0) { in_financial_resources_for_production = 0; }
			if(strcmp(buffer, "total_units_local_inventory") == 0) { in_total_units_local_inventory = 1; }
			if(strcmp(buffer, "/total_units_local_inventory") == 0) { in_total_units_local_inventory = 0; }
			if(strcmp(buffer, "calc_capital_costs") == 0) { in_calc_capital_costs = 1; }
			if(strcmp(buffer, "/calc_capital_costs") == 0) { in_calc_capital_costs = 0; }
			if(strcmp(buffer, "calc_production_costs") == 0) { in_calc_production_costs = 1; }
			if(strcmp(buffer, "/calc_production_costs") == 0) { in_calc_production_costs = 0; }
			if(strcmp(buffer, "firm_productivity") == 0) { in_firm_productivity = 1; }
			if(strcmp(buffer, "/firm_productivity") == 0) { in_firm_productivity = 0; }
			if(strcmp(buffer, "total_productivity_capital_stock") == 0) { in_total_productivity_capital_stock = 1; }
			if(strcmp(buffer, "/total_productivity_capital_stock") == 0) { in_total_productivity_capital_stock = 0; }
			if(strcmp(buffer, "firm_productivity_last_year") == 0) { in_firm_productivity_last_year = 1; }
			if(strcmp(buffer, "/firm_productivity_last_year") == 0) { in_firm_productivity_last_year = 0; }
			if(strcmp(buffer, "firm_productivity_progress") == 0) { in_firm_productivity_progress = 1; }
			if(strcmp(buffer, "/firm_productivity_progress") == 0) { in_firm_productivity_progress = 0; }
			if(strcmp(buffer, "sold_quantity_in_last_calendar_month") == 0) { in_sold_quantity_in_last_calendar_month = 1; }
			if(strcmp(buffer, "/sold_quantity_in_last_calendar_month") == 0) { in_sold_quantity_in_last_calendar_month = 0; }
			if(strcmp(buffer, "last_sold_quantities") == 0) { in_last_sold_quantities = 1; }
			if(strcmp(buffer, "/last_sold_quantities") == 0) { in_last_sold_quantities = 0; }
			if(strcmp(buffer, "last_revenues") == 0) { in_last_revenues = 1; }
			if(strcmp(buffer, "/last_revenues") == 0) { in_last_revenues = 0; }
			if(strcmp(buffer, "set_of_lenders") == 0) { in_set_of_lenders = 1; }
			if(strcmp(buffer, "/set_of_lenders") == 0) { in_set_of_lenders = 0; }
			if(strcmp(buffer, "potential_lenders") == 0) { in_potential_lenders = 1; }
			if(strcmp(buffer, "/potential_lenders") == 0) { in_potential_lenders = 0; }
			if(strcmp(buffer, "number_of_banks_asked") == 0) { in_number_of_banks_asked = 1; }
			if(strcmp(buffer, "/number_of_banks_asked") == 0) { in_number_of_banks_asked = 0; }
			if(strcmp(buffer, "received_interest_daily") == 0) { in_received_interest_daily = 1; }
			if(strcmp(buffer, "/received_interest_daily") == 0) { in_received_interest_daily = 0; }
			if(strcmp(buffer, "received_interest_in_calendar_month") == 0) { in_received_interest_in_calendar_month = 1; }
			if(strcmp(buffer, "/received_interest_in_calendar_month") == 0) { in_received_interest_in_calendar_month = 0; }
			if(strcmp(buffer, "flag_illiquidity_correction") == 0) { in_flag_illiquidity_correction = 1; }
			if(strcmp(buffer, "/flag_illiquidity_correction") == 0) { in_flag_illiquidity_correction = 0; }
			if(strcmp(buffer, "ebit") == 0) { in_ebit = 1; }
			if(strcmp(buffer, "/ebit") == 0) { in_ebit = 0; }
			if(strcmp(buffer, "earnings") == 0) { in_earnings = 1; }
			if(strcmp(buffer, "/earnings") == 0) { in_earnings = 0; }
			if(strcmp(buffer, "tax_rate_corporate") == 0) { in_tax_rate_corporate = 1; }
			if(strcmp(buffer, "/tax_rate_corporate") == 0) { in_tax_rate_corporate = 0; }
			if(strcmp(buffer, "tax_rate_vat") == 0) { in_tax_rate_vat = 1; }
			if(strcmp(buffer, "/tax_rate_vat") == 0) { in_tax_rate_vat = 0; }
			if(strcmp(buffer, "tax_payment") == 0) { in_tax_payment = 1; }
			if(strcmp(buffer, "/tax_payment") == 0) { in_tax_payment = 0; }
			if(strcmp(buffer, "tax_payment_in_calendar_month") == 0) { in_tax_payment_in_calendar_month = 1; }
			if(strcmp(buffer, "/tax_payment_in_calendar_month") == 0) { in_tax_payment_in_calendar_month = 0; }
			if(strcmp(buffer, "net_earnings") == 0) { in_net_earnings = 1; }
			if(strcmp(buffer, "/net_earnings") == 0) { in_net_earnings = 0; }
			if(strcmp(buffer, "earnings_history") == 0) { in_earnings_history = 1; }
			if(strcmp(buffer, "/earnings_history") == 0) { in_earnings_history = 0; }
			if(strcmp(buffer, "previous_net_earnings") == 0) { in_previous_net_earnings = 1; }
			if(strcmp(buffer, "/previous_net_earnings") == 0) { in_previous_net_earnings = 0; }
			if(strcmp(buffer, "total_interest_payment") == 0) { in_total_interest_payment = 1; }
			if(strcmp(buffer, "/total_interest_payment") == 0) { in_total_interest_payment = 0; }
			if(strcmp(buffer, "total_interest_payment_in_calendar_month") == 0) { in_total_interest_payment_in_calendar_month = 1; }
			if(strcmp(buffer, "/total_interest_payment_in_calendar_month") == 0) { in_total_interest_payment_in_calendar_month = 0; }
			if(strcmp(buffer, "total_debt_installment_payment") == 0) { in_total_debt_installment_payment = 1; }
			if(strcmp(buffer, "/total_debt_installment_payment") == 0) { in_total_debt_installment_payment = 0; }
			if(strcmp(buffer, "total_debt_installment_payment_in_calendar_month") == 0) { in_total_debt_installment_payment_in_calendar_month = 1; }
			if(strcmp(buffer, "/total_debt_installment_payment_in_calendar_month") == 0) { in_total_debt_installment_payment_in_calendar_month = 0; }
			if(strcmp(buffer, "total_dividend_payment") == 0) { in_total_dividend_payment = 1; }
			if(strcmp(buffer, "/total_dividend_payment") == 0) { in_total_dividend_payment = 0; }
			if(strcmp(buffer, "total_dividend_payment_in_calendar_month") == 0) { in_total_dividend_payment_in_calendar_month = 1; }
			if(strcmp(buffer, "/total_dividend_payment_in_calendar_month") == 0) { in_total_dividend_payment_in_calendar_month = 0; }
			if(strcmp(buffer, "flag_full_dividend") == 0) { in_flag_full_dividend = 1; }
			if(strcmp(buffer, "/flag_full_dividend") == 0) { in_flag_full_dividend = 0; }
			if(strcmp(buffer, "current_share_price") == 0) { in_current_share_price = 1; }
			if(strcmp(buffer, "/current_share_price") == 0) { in_current_share_price = 0; }
			if(strcmp(buffer, "previous_dividend_per_share") == 0) { in_previous_dividend_per_share = 1; }
			if(strcmp(buffer, "/previous_dividend_per_share") == 0) { in_previous_dividend_per_share = 0; }
			if(strcmp(buffer, "current_dividend_per_share") == 0) { in_current_dividend_per_share = 1; }
			if(strcmp(buffer, "/current_dividend_per_share") == 0) { in_current_dividend_per_share = 0; }
			if(strcmp(buffer, "previous_earnings_per_share") == 0) { in_previous_earnings_per_share = 1; }
			if(strcmp(buffer, "/previous_earnings_per_share") == 0) { in_previous_earnings_per_share = 0; }
			if(strcmp(buffer, "current_earnings_per_share") == 0) { in_current_earnings_per_share = 1; }
			if(strcmp(buffer, "/current_earnings_per_share") == 0) { in_current_earnings_per_share = 0; }
			if(strcmp(buffer, "previous_dividend_per_earnings") == 0) { in_previous_dividend_per_earnings = 1; }
			if(strcmp(buffer, "/previous_dividend_per_earnings") == 0) { in_previous_dividend_per_earnings = 0; }
			if(strcmp(buffer, "current_dividend_per_earnings") == 0) { in_current_dividend_per_earnings = 1; }
			if(strcmp(buffer, "/current_dividend_per_earnings") == 0) { in_current_dividend_per_earnings = 0; }
			if(strcmp(buffer, "debt_earnings_ratio") == 0) { in_debt_earnings_ratio = 1; }
			if(strcmp(buffer, "/debt_earnings_ratio") == 0) { in_debt_earnings_ratio = 0; }
			if(strcmp(buffer, "debt_equity_ratio") == 0) { in_debt_equity_ratio = 1; }
			if(strcmp(buffer, "/debt_equity_ratio") == 0) { in_debt_equity_ratio = 0; }
			if(strcmp(buffer, "price_earnings_ratio") == 0) { in_price_earnings_ratio = 1; }
			if(strcmp(buffer, "/price_earnings_ratio") == 0) { in_price_earnings_ratio = 0; }
			if(strcmp(buffer, "retained_earnings_ratio") == 0) { in_retained_earnings_ratio = 1; }
			if(strcmp(buffer, "/retained_earnings_ratio") == 0) { in_retained_earnings_ratio = 0; }
			if(strcmp(buffer, "earnings_per_share_ratio_growth") == 0) { in_earnings_per_share_ratio_growth = 1; }
			if(strcmp(buffer, "/earnings_per_share_ratio_growth") == 0) { in_earnings_per_share_ratio_growth = 0; }
			if(strcmp(buffer, "critical_price_earnings_ratio") == 0) { in_critical_price_earnings_ratio = 1; }
			if(strcmp(buffer, "/critical_price_earnings_ratio") == 0) { in_critical_price_earnings_ratio = 0; }
			if(strcmp(buffer, "critical_earnings_per_share_ratio") == 0) { in_critical_earnings_per_share_ratio = 1; }
			if(strcmp(buffer, "/critical_earnings_per_share_ratio") == 0) { in_critical_earnings_per_share_ratio = 0; }
			if(strcmp(buffer, "loans") == 0) { in_loans = 1; }
			if(strcmp(buffer, "/loans") == 0) { in_loans = 0; }
			if(strcmp(buffer, "total_debt") == 0) { in_total_debt = 1; }
			if(strcmp(buffer, "/total_debt") == 0) { in_total_debt = 0; }
			if(strcmp(buffer, "target_debt") == 0) { in_target_debt = 1; }
			if(strcmp(buffer, "/target_debt") == 0) { in_target_debt = 0; }
			if(strcmp(buffer, "total_debt_balance_sheet") == 0) { in_total_debt_balance_sheet = 1; }
			if(strcmp(buffer, "/total_debt_balance_sheet") == 0) { in_total_debt_balance_sheet = 0; }
			if(strcmp(buffer, "total_value_local_inventory") == 0) { in_total_value_local_inventory = 1; }
			if(strcmp(buffer, "/total_value_local_inventory") == 0) { in_total_value_local_inventory = 0; }
			if(strcmp(buffer, "total_value_local_inventory_balance_sheet") == 0) { in_total_value_local_inventory_balance_sheet = 1; }
			if(strcmp(buffer, "/total_value_local_inventory_balance_sheet") == 0) { in_total_value_local_inventory_balance_sheet = 0; }
			if(strcmp(buffer, "total_units_capital_stock") == 0) { in_total_units_capital_stock = 1; }
			if(strcmp(buffer, "/total_units_capital_stock") == 0) { in_total_units_capital_stock = 0; }
			if(strcmp(buffer, "total_value_capital_stock") == 0) { in_total_value_capital_stock = 1; }
			if(strcmp(buffer, "/total_value_capital_stock") == 0) { in_total_value_capital_stock = 0; }
			if(strcmp(buffer, "total_value_capital_stock_balance_sheet") == 0) { in_total_value_capital_stock_balance_sheet = 1; }
			if(strcmp(buffer, "/total_value_capital_stock_balance_sheet") == 0) { in_total_value_capital_stock_balance_sheet = 0; }
			if(strcmp(buffer, "total_capital_depreciation_value") == 0) { in_total_capital_depreciation_value = 1; }
			if(strcmp(buffer, "/total_capital_depreciation_value") == 0) { in_total_capital_depreciation_value = 0; }
			if(strcmp(buffer, "total_capital_depreciation_units") == 0) { in_total_capital_depreciation_units = 1; }
			if(strcmp(buffer, "/total_capital_depreciation_units") == 0) { in_total_capital_depreciation_units = 0; }
			if(strcmp(buffer, "total_assets") == 0) { in_total_assets = 1; }
			if(strcmp(buffer, "/total_assets") == 0) { in_total_assets = 0; }
			if(strcmp(buffer, "equity") == 0) { in_equity = 1; }
			if(strcmp(buffer, "/equity") == 0) { in_equity = 0; }
			if(strcmp(buffer, "equity_balance_sheet") == 0) { in_equity_balance_sheet = 1; }
			if(strcmp(buffer, "/equity_balance_sheet") == 0) { in_equity_balance_sheet = 0; }
			if(strcmp(buffer, "production_liquidity_needs") == 0) { in_production_liquidity_needs = 1; }
			if(strcmp(buffer, "/production_liquidity_needs") == 0) { in_production_liquidity_needs = 0; }
			if(strcmp(buffer, "financial_liquidity_needs") == 0) { in_financial_liquidity_needs = 1; }
			if(strcmp(buffer, "/financial_liquidity_needs") == 0) { in_financial_liquidity_needs = 0; }
			if(strcmp(buffer, "total_financial_needs") == 0) { in_total_financial_needs = 1; }
			if(strcmp(buffer, "/total_financial_needs") == 0) { in_total_financial_needs = 0; }
			if(strcmp(buffer, "external_financial_needs") == 0) { in_external_financial_needs = 1; }
			if(strcmp(buffer, "/external_financial_needs") == 0) { in_external_financial_needs = 0; }
			if(strcmp(buffer, "earnings_per_share") == 0) { in_earnings_per_share = 1; }
			if(strcmp(buffer, "/earnings_per_share") == 0) { in_earnings_per_share = 0; }
			if(strcmp(buffer, "retained_earnings") == 0) { in_retained_earnings = 1; }
			if(strcmp(buffer, "/retained_earnings") == 0) { in_retained_earnings = 0; }
			if(strcmp(buffer, "total_payments") == 0) { in_total_payments = 1; }
			if(strcmp(buffer, "/total_payments") == 0) { in_total_payments = 0; }
			if(strcmp(buffer, "previous_shares_outstanding") == 0) { in_previous_shares_outstanding = 1; }
			if(strcmp(buffer, "/previous_shares_outstanding") == 0) { in_previous_shares_outstanding = 0; }
			if(strcmp(buffer, "minsky_state") == 0) { in_minsky_state = 1; }
			if(strcmp(buffer, "/minsky_state") == 0) { in_minsky_state = 0; }
			if(strcmp(buffer, "minsky_state_1") == 0) { in_minsky_state_1 = 1; }
			if(strcmp(buffer, "/minsky_state_1") == 0) { in_minsky_state_1 = 0; }
			if(strcmp(buffer, "minsky_state_2") == 0) { in_minsky_state_2 = 1; }
			if(strcmp(buffer, "/minsky_state_2") == 0) { in_minsky_state_2 = 0; }
			if(strcmp(buffer, "minsky_state_3") == 0) { in_minsky_state_3 = 1; }
			if(strcmp(buffer, "/minsky_state_3") == 0) { in_minsky_state_3 = 0; }
			if(strcmp(buffer, "minsky_state_4") == 0) { in_minsky_state_4 = 1; }
			if(strcmp(buffer, "/minsky_state_4") == 0) { in_minsky_state_4 = 0; }
			if(strcmp(buffer, "minsky_state_5") == 0) { in_minsky_state_5 = 1; }
			if(strcmp(buffer, "/minsky_state_5") == 0) { in_minsky_state_5 = 0; }
			if(strcmp(buffer, "minsky_state_20") == 0) { in_minsky_state_20 = 1; }
			if(strcmp(buffer, "/minsky_state_20") == 0) { in_minsky_state_20 = 0; }
			if(strcmp(buffer, "minsky_state_21") == 0) { in_minsky_state_21 = 1; }
			if(strcmp(buffer, "/minsky_state_21") == 0) { in_minsky_state_21 = 0; }
			if(strcmp(buffer, "minsky_state_22") == 0) { in_minsky_state_22 = 1; }
			if(strcmp(buffer, "/minsky_state_22") == 0) { in_minsky_state_22 = 0; }
			if(strcmp(buffer, "minsky_state_23") == 0) { in_minsky_state_23 = 1; }
			if(strcmp(buffer, "/minsky_state_23") == 0) { in_minsky_state_23 = 0; }
			if(strcmp(buffer, "minsky_state_30") == 0) { in_minsky_state_30 = 1; }
			if(strcmp(buffer, "/minsky_state_30") == 0) { in_minsky_state_30 = 0; }
			if(strcmp(buffer, "minsky_state_31") == 0) { in_minsky_state_31 = 1; }
			if(strcmp(buffer, "/minsky_state_31") == 0) { in_minsky_state_31 = 0; }
			if(strcmp(buffer, "minsky_state_32") == 0) { in_minsky_state_32 = 1; }
			if(strcmp(buffer, "/minsky_state_32") == 0) { in_minsky_state_32 = 0; }
			if(strcmp(buffer, "minsky_state_33") == 0) { in_minsky_state_33 = 1; }
			if(strcmp(buffer, "/minsky_state_33") == 0) { in_minsky_state_33 = 0; }
			if(strcmp(buffer, "minsky_state_40") == 0) { in_minsky_state_40 = 1; }
			if(strcmp(buffer, "/minsky_state_40") == 0) { in_minsky_state_40 = 0; }
			if(strcmp(buffer, "minsky_state_41") == 0) { in_minsky_state_41 = 1; }
			if(strcmp(buffer, "/minsky_state_41") == 0) { in_minsky_state_41 = 0; }
			if(strcmp(buffer, "minsky_state_42") == 0) { in_minsky_state_42 = 1; }
			if(strcmp(buffer, "/minsky_state_42") == 0) { in_minsky_state_42 = 0; }
			if(strcmp(buffer, "minsky_state_43") == 0) { in_minsky_state_43 = 1; }
			if(strcmp(buffer, "/minsky_state_43") == 0) { in_minsky_state_43 = 0; }
			if(strcmp(buffer, "age_at_bankruptcy") == 0) { in_age_at_bankruptcy = 1; }
			if(strcmp(buffer, "/age_at_bankruptcy") == 0) { in_age_at_bankruptcy = 0; }
			if(strcmp(buffer, "debt_at_bankruptcy") == 0) { in_debt_at_bankruptcy = 1; }
			if(strcmp(buffer, "/debt_at_bankruptcy") == 0) { in_debt_at_bankruptcy = 0; }
			if(strcmp(buffer, "equity_at_bankruptcy") == 0) { in_equity_at_bankruptcy = 1; }
			if(strcmp(buffer, "/equity_at_bankruptcy") == 0) { in_equity_at_bankruptcy = 0; }
			if(strcmp(buffer, "no_employees_at_bankruptcy") == 0) { in_no_employees_at_bankruptcy = 1; }
			if(strcmp(buffer, "/no_employees_at_bankruptcy") == 0) { in_no_employees_at_bankruptcy = 0; }
			if(strcmp(buffer, "equity_asset_ratio") == 0) { in_equity_asset_ratio = 1; }
			if(strcmp(buffer, "/equity_asset_ratio") == 0) { in_equity_asset_ratio = 0; }
			if(strcmp(buffer, "profit_asset_ratio") == 0) { in_profit_asset_ratio = 1; }
			if(strcmp(buffer, "/profit_asset_ratio") == 0) { in_profit_asset_ratio = 0; }
			if(strcmp(buffer, "sales_asset_ratio") == 0) { in_sales_asset_ratio = 1; }
			if(strcmp(buffer, "/sales_asset_ratio") == 0) { in_sales_asset_ratio = 0; }
			if(strcmp(buffer, "investment_asset_ratio") == 0) { in_investment_asset_ratio = 1; }
			if(strcmp(buffer, "/investment_asset_ratio") == 0) { in_investment_asset_ratio = 0; }
			if(strcmp(buffer, "total_income") == 0) { in_total_income = 1; }
			if(strcmp(buffer, "/total_income") == 0) { in_total_income = 0; }
			if(strcmp(buffer, "total_liabilities") == 0) { in_total_liabilities = 1; }
			if(strcmp(buffer, "/total_liabilities") == 0) { in_total_liabilities = 0; }
			if(strcmp(buffer, "total_expenses") == 0) { in_total_expenses = 1; }
			if(strcmp(buffer, "/total_expenses") == 0) { in_total_expenses = 0; }
			if(strcmp(buffer, "current_shares_outstanding") == 0) { in_current_shares_outstanding = 1; }
			if(strcmp(buffer, "/current_shares_outstanding") == 0) { in_current_shares_outstanding = 0; }
			if(strcmp(buffer, "employees") == 0) { in_employees = 1; }
			if(strcmp(buffer, "/employees") == 0) { in_employees = 0; }
			if(strcmp(buffer, "r_and_d_employees") == 0) { in_r_and_d_employees = 1; }
			if(strcmp(buffer, "/r_and_d_employees") == 0) { in_r_and_d_employees = 0; }
			if(strcmp(buffer, "wage_offer") == 0) { in_wage_offer = 1; }
			if(strcmp(buffer, "/wage_offer") == 0) { in_wage_offer = 0; }
			if(strcmp(buffer, "technology") == 0) { in_technology = 1; }
			if(strcmp(buffer, "/technology") == 0) { in_technology = 0; }
			if(strcmp(buffer, "no_employees") == 0) { in_no_employees = 1; }
			if(strcmp(buffer, "/no_employees") == 0) { in_no_employees = 0; }
			if(strcmp(buffer, "no_employees_skill_1") == 0) { in_no_employees_skill_1 = 1; }
			if(strcmp(buffer, "/no_employees_skill_1") == 0) { in_no_employees_skill_1 = 0; }
			if(strcmp(buffer, "no_employees_skill_2") == 0) { in_no_employees_skill_2 = 1; }
			if(strcmp(buffer, "/no_employees_skill_2") == 0) { in_no_employees_skill_2 = 0; }
			if(strcmp(buffer, "no_employees_skill_3") == 0) { in_no_employees_skill_3 = 1; }
			if(strcmp(buffer, "/no_employees_skill_3") == 0) { in_no_employees_skill_3 = 0; }
			if(strcmp(buffer, "no_employees_skill_4") == 0) { in_no_employees_skill_4 = 1; }
			if(strcmp(buffer, "/no_employees_skill_4") == 0) { in_no_employees_skill_4 = 0; }
			if(strcmp(buffer, "no_employees_skill_5") == 0) { in_no_employees_skill_5 = 1; }
			if(strcmp(buffer, "/no_employees_skill_5") == 0) { in_no_employees_skill_5 = 0; }
			if(strcmp(buffer, "vacancies") == 0) { in_vacancies = 1; }
			if(strcmp(buffer, "/vacancies") == 0) { in_vacancies = 0; }
			if(strcmp(buffer, "no_redundancies") == 0) { in_no_redundancies = 1; }
			if(strcmp(buffer, "/no_redundancies") == 0) { in_no_redundancies = 0; }
			if(strcmp(buffer, "no_redundancies_r_and_d_employees") == 0) { in_no_redundancies_r_and_d_employees = 1; }
			if(strcmp(buffer, "/no_redundancies_r_and_d_employees") == 0) { in_no_redundancies_r_and_d_employees = 0; }
			if(strcmp(buffer, "vacancies_r_and_d_employees") == 0) { in_vacancies_r_and_d_employees = 1; }
			if(strcmp(buffer, "/vacancies_r_and_d_employees") == 0) { in_vacancies_r_and_d_employees = 0; }
			if(strcmp(buffer, "posted_vacancies") == 0) { in_posted_vacancies = 1; }
			if(strcmp(buffer, "/posted_vacancies") == 0) { in_posted_vacancies = 0; }
			if(strcmp(buffer, "posted_vacancies_r_and_d_employees") == 0) { in_posted_vacancies_r_and_d_employees = 1; }
			if(strcmp(buffer, "/posted_vacancies_r_and_d_employees") == 0) { in_posted_vacancies_r_and_d_employees = 0; }
			if(strcmp(buffer, "average_g_skill") == 0) { in_average_g_skill = 1; }
			if(strcmp(buffer, "/average_g_skill") == 0) { in_average_g_skill = 0; }
			if(strcmp(buffer, "average_adaptation_speed_specific_skills") == 0) { in_average_adaptation_speed_specific_skills = 1; }
			if(strcmp(buffer, "/average_adaptation_speed_specific_skills") == 0) { in_average_adaptation_speed_specific_skills = 0; }
			if(strcmp(buffer, "list_adaptation_speed_per_skill_group") == 0) { in_list_adaptation_speed_per_skill_group = 1; }
			if(strcmp(buffer, "/list_adaptation_speed_per_skill_group") == 0) { in_list_adaptation_speed_per_skill_group = 0; }
			if(strcmp(buffer, "average_s_skill_of_1") == 0) { in_average_s_skill_of_1 = 1; }
			if(strcmp(buffer, "/average_s_skill_of_1") == 0) { in_average_s_skill_of_1 = 0; }
			if(strcmp(buffer, "average_s_skill_of_2") == 0) { in_average_s_skill_of_2 = 1; }
			if(strcmp(buffer, "/average_s_skill_of_2") == 0) { in_average_s_skill_of_2 = 0; }
			if(strcmp(buffer, "average_s_skill_of_3") == 0) { in_average_s_skill_of_3 = 1; }
			if(strcmp(buffer, "/average_s_skill_of_3") == 0) { in_average_s_skill_of_3 = 0; }
			if(strcmp(buffer, "average_s_skill_of_4") == 0) { in_average_s_skill_of_4 = 1; }
			if(strcmp(buffer, "/average_s_skill_of_4") == 0) { in_average_s_skill_of_4 = 0; }
			if(strcmp(buffer, "average_s_skill_of_5") == 0) { in_average_s_skill_of_5 = 1; }
			if(strcmp(buffer, "/average_s_skill_of_5") == 0) { in_average_s_skill_of_5 = 0; }
			if(strcmp(buffer, "wage_offer_for_skill_1") == 0) { in_wage_offer_for_skill_1 = 1; }
			if(strcmp(buffer, "/wage_offer_for_skill_1") == 0) { in_wage_offer_for_skill_1 = 0; }
			if(strcmp(buffer, "wage_offer_for_skill_2") == 0) { in_wage_offer_for_skill_2 = 1; }
			if(strcmp(buffer, "/wage_offer_for_skill_2") == 0) { in_wage_offer_for_skill_2 = 0; }
			if(strcmp(buffer, "wage_offer_for_skill_3") == 0) { in_wage_offer_for_skill_3 = 1; }
			if(strcmp(buffer, "/wage_offer_for_skill_3") == 0) { in_wage_offer_for_skill_3 = 0; }
			if(strcmp(buffer, "wage_offer_for_skill_4") == 0) { in_wage_offer_for_skill_4 = 1; }
			if(strcmp(buffer, "/wage_offer_for_skill_4") == 0) { in_wage_offer_for_skill_4 = 0; }
			if(strcmp(buffer, "wage_offer_for_skill_5") == 0) { in_wage_offer_for_skill_5 = 1; }
			if(strcmp(buffer, "/wage_offer_for_skill_5") == 0) { in_wage_offer_for_skill_5 = 0; }
			if(strcmp(buffer, "wage_offer_for_r_and_d_employees") == 0) { in_wage_offer_for_r_and_d_employees = 1; }
			if(strcmp(buffer, "/wage_offer_for_r_and_d_employees") == 0) { in_wage_offer_for_r_and_d_employees = 0; }
			if(strcmp(buffer, "base_wage_offer_r_and_d") == 0) { in_base_wage_offer_r_and_d = 1; }
			if(strcmp(buffer, "/base_wage_offer_r_and_d") == 0) { in_base_wage_offer_r_and_d = 0; }
			if(strcmp(buffer, "employees_needed") == 0) { in_employees_needed = 1; }
			if(strcmp(buffer, "/employees_needed") == 0) { in_employees_needed = 0; }
			if(strcmp(buffer, "firm_balance_sheet_calendar") == 0) { in_firm_balance_sheet_calendar = 1; }
			if(strcmp(buffer, "/firm_balance_sheet_calendar") == 0) { in_firm_balance_sheet_calendar = 0; }
			if(strcmp(buffer, "firm_stocks_calendar") == 0) { in_firm_stocks_calendar = 1; }
			if(strcmp(buffer, "/firm_stocks_calendar") == 0) { in_firm_stocks_calendar = 0; }
			if(strcmp(buffer, "firm_outflows_calendar") == 0) { in_firm_outflows_calendar = 1; }
			if(strcmp(buffer, "/firm_outflows_calendar") == 0) { in_firm_outflows_calendar = 0; }
			if(strcmp(buffer, "firm_inflows_calendar") == 0) { in_firm_inflows_calendar = 1; }
			if(strcmp(buffer, "/firm_inflows_calendar") == 0) { in_firm_inflows_calendar = 0; }
			if(strcmp(buffer, "age") == 0) { in_age = 1; }
			if(strcmp(buffer, "/age") == 0) { in_age = 0; }
			if(strcmp(buffer, "transfer_payment") == 0) { in_transfer_payment = 1; }
			if(strcmp(buffer, "/transfer_payment") == 0) { in_transfer_payment = 0; }
			if(strcmp(buffer, "subsidy_pct") == 0) { in_subsidy_pct = 1; }
			if(strcmp(buffer, "/subsidy_pct") == 0) { in_subsidy_pct = 0; }
			if(strcmp(buffer, "active") == 0) { in_active = 1; }
			if(strcmp(buffer, "/active") == 0) { in_active = 0; }
			if(strcmp(buffer, "inactive") == 0) { in_inactive = 1; }
			if(strcmp(buffer, "/inactive") == 0) { in_inactive = 0; }
			if(strcmp(buffer, "zero_output") == 0) { in_zero_output = 1; }
			if(strcmp(buffer, "/zero_output") == 0) { in_zero_output = 0; }
			if(strcmp(buffer, "bankruptcy_idle_counter") == 0) { in_bankruptcy_idle_counter = 1; }
			if(strcmp(buffer, "/bankruptcy_idle_counter") == 0) { in_bankruptcy_idle_counter = 0; }
			if(strcmp(buffer, "bankruptcy_state") == 0) { in_bankruptcy_state = 1; }
			if(strcmp(buffer, "/bankruptcy_state") == 0) { in_bankruptcy_state = 0; }
			if(strcmp(buffer, "bankruptcy_insolvency_state") == 0) { in_bankruptcy_insolvency_state = 1; }
			if(strcmp(buffer, "/bankruptcy_insolvency_state") == 0) { in_bankruptcy_insolvency_state = 0; }
			if(strcmp(buffer, "bankruptcy_illiquidity_state") == 0) { in_bankruptcy_illiquidity_state = 1; }
			if(strcmp(buffer, "/bankruptcy_illiquidity_state") == 0) { in_bankruptcy_illiquidity_state = 0; }
			if(strcmp(buffer, "financial_crisis_state") == 0) { in_financial_crisis_state = 1; }
			if(strcmp(buffer, "/financial_crisis_state") == 0) { in_financial_crisis_state = 0; }
			if(strcmp(buffer, "average_s_skill_from_eurostat") == 0) { in_average_s_skill_from_eurostat = 1; }
			if(strcmp(buffer, "/average_s_skill_from_eurostat") == 0) { in_average_s_skill_from_eurostat = 0; }
			if(strcmp(buffer, "average_output_from_eurostat") == 0) { in_average_output_from_eurostat = 1; }
			if(strcmp(buffer, "/average_output_from_eurostat") == 0) { in_average_output_from_eurostat = 0; }
			if(strcmp(buffer, "subsidy_payment") == 0) { in_subsidy_payment = 1; }
			if(strcmp(buffer, "/subsidy_payment") == 0) { in_subsidy_payment = 0; }
			if(strcmp(buffer, "current_price_index") == 0) { in_current_price_index = 1; }
			if(strcmp(buffer, "/current_price_index") == 0) { in_current_price_index = 0; }
			if(strcmp(buffer, "current_quality_index") == 0) { in_current_quality_index = 1; }
			if(strcmp(buffer, "/current_quality_index") == 0) { in_current_quality_index = 0; }
			if(strcmp(buffer, "no_competitors") == 0) { in_no_competitors = 1; }
			if(strcmp(buffer, "/no_competitors") == 0) { in_no_competitors = 0; }
			if(strcmp(buffer, "indicator_earnings") == 0) { in_indicator_earnings = 1; }
			if(strcmp(buffer, "/indicator_earnings") == 0) { in_indicator_earnings = 0; }
			if(strcmp(buffer, "indicator_capital_costs") == 0) { in_indicator_capital_costs = 1; }
			if(strcmp(buffer, "/indicator_capital_costs") == 0) { in_indicator_capital_costs = 0; }
			if(strcmp(buffer, "indicator_size_by_capital_stock") == 0) { in_indicator_size_by_capital_stock = 1; }
			if(strcmp(buffer, "/indicator_size_by_capital_stock") == 0) { in_indicator_size_by_capital_stock = 0; }
			if(strcmp(buffer, "market_research_sample_size") == 0) { in_market_research_sample_size = 1; }
			if(strcmp(buffer, "/market_research_sample_size") == 0) { in_market_research_sample_size = 0; }
			if(strcmp(buffer, "product_innovation") == 0) { in_product_innovation = 1; }
			if(strcmp(buffer, "/product_innovation") == 0) { in_product_innovation = 0; }
			if(strcmp(buffer, "regional_analysis") == 0) { in_regional_analysis = 1; }
			if(strcmp(buffer, "/regional_analysis") == 0) { in_regional_analysis = 0; }
			if(strcmp(buffer, "day_of_year_market_research") == 0) { in_day_of_year_market_research = 1; }
			if(strcmp(buffer, "/day_of_year_market_research") == 0) { in_day_of_year_market_research = 0; }
			if(strcmp(buffer, "actual_sample_size") == 0) { in_actual_sample_size = 1; }
			if(strcmp(buffer, "/actual_sample_size") == 0) { in_actual_sample_size = 0; }
			if(strcmp(buffer, "last_market_sizes") == 0) { in_last_market_sizes = 1; }
			if(strcmp(buffer, "/last_market_sizes") == 0) { in_last_market_sizes = 0; }
			if(strcmp(buffer, "price_range_pricing") == 0) { in_price_range_pricing = 1; }
			if(strcmp(buffer, "/price_range_pricing") == 0) { in_price_range_pricing = 0; }
			if(strcmp(buffer, "price_range_innovation") == 0) { in_price_range_innovation = 1; }
			if(strcmp(buffer, "/price_range_innovation") == 0) { in_price_range_innovation = 0; }
			if(strcmp(buffer, "new_product_released") == 0) { in_new_product_released = 1; }
			if(strcmp(buffer, "/new_product_released") == 0) { in_new_product_released = 0; }
			if(strcmp(buffer, "prospective_variables") == 0) { in_prospective_variables = 1; }
			if(strcmp(buffer, "/prospective_variables") == 0) { in_prospective_variables = 0; }
			if(strcmp(buffer, "price_at_questionnaire") == 0) { in_price_at_questionnaire = 1; }
			if(strcmp(buffer, "/price_at_questionnaire") == 0) { in_price_at_questionnaire = 0; }
			if(strcmp(buffer, "price_index_at_questionnaire") == 0) { in_price_index_at_questionnaire = 1; }
			if(strcmp(buffer, "/price_index_at_questionnaire") == 0) { in_price_index_at_questionnaire = 0; }
			if(strcmp(buffer, "best_pricing_strategies") == 0) { in_best_pricing_strategies = 1; }
			if(strcmp(buffer, "/best_pricing_strategies") == 0) { in_best_pricing_strategies = 0; }
			if(strcmp(buffer, "best_pricing_abandon_strategy") == 0) { in_best_pricing_abandon_strategy = 1; }
			if(strcmp(buffer, "/best_pricing_abandon_strategy") == 0) { in_best_pricing_abandon_strategy = 0; }
			if(strcmp(buffer, "intermediate_quality") == 0) { in_intermediate_quality = 1; }
			if(strcmp(buffer, "/intermediate_quality") == 0) { in_intermediate_quality = 0; }
			if(strcmp(buffer, "no_employees_product_innovation_fundable") == 0) { in_no_employees_product_innovation_fundable = 1; }
			if(strcmp(buffer, "/no_employees_product_innovation_fundable") == 0) { in_no_employees_product_innovation_fundable = 0; }
			if(strcmp(buffer, "r_and_d_probability_for_incremental_success") == 0) { in_r_and_d_probability_for_incremental_success = 1; }
			if(strcmp(buffer, "/r_and_d_probability_for_incremental_success") == 0) { in_r_and_d_probability_for_incremental_success = 0; }
			if(strcmp(buffer, "market_research_active") == 0) { in_market_research_active = 1; }
			if(strcmp(buffer, "/market_research_active") == 0) { in_market_research_active = 0; }
			if(strcmp(buffer, "innovation_successful") == 0) { in_innovation_successful = 1; }
			if(strcmp(buffer, "/innovation_successful") == 0) { in_innovation_successful = 0; }
			if(strcmp(buffer, "actual_market_share") == 0) { in_actual_market_share = 1; }
			if(strcmp(buffer, "/actual_market_share") == 0) { in_actual_market_share = 0; }
			if(strcmp(buffer, "market_size") == 0) { in_market_size = 1; }
			if(strcmp(buffer, "/market_size") == 0) { in_market_size = 0; }
			if(strcmp(buffer, "estimated_market_size") == 0) { in_estimated_market_size = 1; }
			if(strcmp(buffer, "/estimated_market_size") == 0) { in_estimated_market_size = 0; }
			if(strcmp(buffer, "linear_regression_estimators") == 0) { in_linear_regression_estimators = 1; }
			if(strcmp(buffer, "/linear_regression_estimators") == 0) { in_linear_regression_estimators = 0; }
			if(strcmp(buffer, "linear_regression_market_size") == 0) { in_linear_regression_market_size = 1; }
			if(strcmp(buffer, "/linear_regression_market_size") == 0) { in_linear_regression_market_size = 0; }
			if(strcmp(buffer, "counter_month_since_last_price_setting") == 0) { in_counter_month_since_last_price_setting = 1; }
			if(strcmp(buffer, "/counter_month_since_last_price_setting") == 0) { in_counter_month_since_last_price_setting = 0; }
			if(strcmp(buffer, "demand_function_pricing") == 0) { in_demand_function_pricing = 1; }
			if(strcmp(buffer, "/demand_function_pricing") == 0) { in_demand_function_pricing = 0; }
			if(strcmp(buffer, "demand_functions_product_innovation") == 0) { in_demand_functions_product_innovation = 1; }
			if(strcmp(buffer, "/demand_functions_product_innovation") == 0) { in_demand_functions_product_innovation = 0; }
			if(strcmp(buffer, "market_research_delayed") == 0) { in_market_research_delayed = 1; }
			if(strcmp(buffer, "/market_research_delayed") == 0) { in_market_research_delayed = 0; }
			if(strcmp(buffer, "market_research_data_pricing") == 0) { in_market_research_data_pricing = 1; }
			if(strcmp(buffer, "/market_research_data_pricing") == 0) { in_market_research_data_pricing = 0; }
			if(strcmp(buffer, "market_research_data_product_innovation") == 0) { in_market_research_data_product_innovation = 1; }
			if(strcmp(buffer, "/market_research_data_product_innovation") == 0) { in_market_research_data_product_innovation = 0; }
			if(strcmp(buffer, "expected_earnings_per_month") == 0) { in_expected_earnings_per_month = 1; }
			if(strcmp(buffer, "/expected_earnings_per_month") == 0) { in_expected_earnings_per_month = 0; }
			if(strcmp(buffer, "expected_price_choices") == 0) { in_expected_price_choices = 1; }
			if(strcmp(buffer, "/expected_price_choices") == 0) { in_expected_price_choices = 0; }
			if(strcmp(buffer, "no_considered_qualities") == 0) { in_no_considered_qualities = 1; }
			if(strcmp(buffer, "/no_considered_qualities") == 0) { in_no_considered_qualities = 0; }
			if(strcmp(buffer, "last_interest_rate_for_loans") == 0) { in_last_interest_rate_for_loans = 1; }
			if(strcmp(buffer, "/last_interest_rate_for_loans") == 0) { in_last_interest_rate_for_loans = 0; }
			if(strcmp(buffer, "cum_earnings_last_r_d_project") == 0) { in_cum_earnings_last_r_d_project = 1; }
			if(strcmp(buffer, "/cum_earnings_last_r_d_project") == 0) { in_cum_earnings_last_r_d_project = 0; }
			if(strcmp(buffer, "cum_r_d_investments") == 0) { in_cum_r_d_investments = 1; }
			if(strcmp(buffer, "/cum_r_d_investments") == 0) { in_cum_r_d_investments = 0; }
			if(strcmp(buffer, "r_d_investments_last_project") == 0) { in_r_d_investments_last_project = 1; }
			if(strcmp(buffer, "/r_d_investments_last_project") == 0) { in_r_d_investments_last_project = 0; }
			if(strcmp(buffer, "total_person_months") == 0) { in_total_person_months = 1; }
			if(strcmp(buffer, "/total_person_months") == 0) { in_total_person_months = 0; }
			if(strcmp(buffer, "cum_person_months") == 0) { in_cum_person_months = 1; }
			if(strcmp(buffer, "/cum_person_months") == 0) { in_cum_person_months = 0; }
			if(strcmp(buffer, "actual_r_and_d_success_probability") == 0) { in_actual_r_and_d_success_probability = 1; }
			if(strcmp(buffer, "/actual_r_and_d_success_probability") == 0) { in_actual_r_and_d_success_probability = 0; }
			if(strcmp(buffer, "last_quality") == 0) { in_last_quality = 1; }
			if(strcmp(buffer, "/last_quality") == 0) { in_last_quality = 0; }
			if(strcmp(buffer, "quality_change") == 0) { in_quality_change = 1; }
			if(strcmp(buffer, "/quality_change") == 0) { in_quality_change = 0; }
			if(strcmp(buffer, "expected_sold_quantity_per_month") == 0) { in_expected_sold_quantity_per_month = 1; }
			if(strcmp(buffer, "/expected_sold_quantity_per_month") == 0) { in_expected_sold_quantity_per_month = 0; }
			if(strcmp(buffer, "estimated_market_share") == 0) { in_estimated_market_share = 1; }
			if(strcmp(buffer, "/estimated_market_share") == 0) { in_estimated_market_share = 0; }
			if(strcmp(buffer, "estimated_market_share_beginning_of_year") == 0) { in_estimated_market_share_beginning_of_year = 1; }
			if(strcmp(buffer, "/estimated_market_share_beginning_of_year") == 0) { in_estimated_market_share_beginning_of_year = 0; }
			if(strcmp(buffer, "estimated_market_share_end_of_year") == 0) { in_estimated_market_share_end_of_year = 1; }
			if(strcmp(buffer, "/estimated_market_share_end_of_year") == 0) { in_estimated_market_share_end_of_year = 0; }
			if(strcmp(buffer, "estimated_yearly_earnings") == 0) { in_estimated_yearly_earnings = 1; }
			if(strcmp(buffer, "/estimated_yearly_earnings") == 0) { in_estimated_yearly_earnings = 0; }
			if(strcmp(buffer, "expected_earnings_and_costs_over_year") == 0) { in_expected_earnings_and_costs_over_year = 1; }
			if(strcmp(buffer, "/expected_earnings_and_costs_over_year") == 0) { in_expected_earnings_and_costs_over_year = 0; }
			if(strcmp(buffer, "expected_output_in_current_month") == 0) { in_expected_output_in_current_month = 1; }
			if(strcmp(buffer, "/expected_output_in_current_month") == 0) { in_expected_output_in_current_month = 0; }
			if(strcmp(buffer, "expected_profit_in_current_month") == 0) { in_expected_profit_in_current_month = 1; }
			if(strcmp(buffer, "/expected_profit_in_current_month") == 0) { in_expected_profit_in_current_month = 0; }
			if(strcmp(buffer, "expected_labor_costs_in_current_month") == 0) { in_expected_labor_costs_in_current_month = 1; }
			if(strcmp(buffer, "/expected_labor_costs_in_current_month") == 0) { in_expected_labor_costs_in_current_month = 0; }
			if(strcmp(buffer, "expected_capital_costs_in_current_month") == 0) { in_expected_capital_costs_in_current_month = 1; }
			if(strcmp(buffer, "/expected_capital_costs_in_current_month") == 0) { in_expected_capital_costs_in_current_month = 0; }
			if(strcmp(buffer, "expected_interests_in_current_month") == 0) { in_expected_interests_in_current_month = 1; }
			if(strcmp(buffer, "/expected_interests_in_current_month") == 0) { in_expected_interests_in_current_month = 0; }
			if(strcmp(buffer, "expected_output_in_previous_month") == 0) { in_expected_output_in_previous_month = 1; }
			if(strcmp(buffer, "/expected_output_in_previous_month") == 0) { in_expected_output_in_previous_month = 0; }
			if(strcmp(buffer, "expected_actual_sold_quantity_in_previous_month") == 0) { in_expected_actual_sold_quantity_in_previous_month = 1; }
			if(strcmp(buffer, "/expected_actual_sold_quantity_in_previous_month") == 0) { in_expected_actual_sold_quantity_in_previous_month = 0; }
			if(strcmp(buffer, "expected_actual_sold_quantity_in_current_month") == 0) { in_expected_actual_sold_quantity_in_current_month = 1; }
			if(strcmp(buffer, "/expected_actual_sold_quantity_in_current_month") == 0) { in_expected_actual_sold_quantity_in_current_month = 0; }
			if(strcmp(buffer, "expected_labor_costs_in_previous_month") == 0) { in_expected_labor_costs_in_previous_month = 1; }
			if(strcmp(buffer, "/expected_labor_costs_in_previous_month") == 0) { in_expected_labor_costs_in_previous_month = 0; }
			if(strcmp(buffer, "expected_capital_costs_in_previous_month") == 0) { in_expected_capital_costs_in_previous_month = 1; }
			if(strcmp(buffer, "/expected_capital_costs_in_previous_month") == 0) { in_expected_capital_costs_in_previous_month = 0; }
			if(strcmp(buffer, "expected_interests_in_previous_month") == 0) { in_expected_interests_in_previous_month = 1; }
			if(strcmp(buffer, "/expected_interests_in_previous_month") == 0) { in_expected_interests_in_previous_month = 0; }
			if(strcmp(buffer, "expected_profit_in_previous_month") == 0) { in_expected_profit_in_previous_month = 1; }
			if(strcmp(buffer, "/expected_profit_in_previous_month") == 0) { in_expected_profit_in_previous_month = 0; }
			if(strcmp(buffer, "expected_wage_in_current_month") == 0) { in_expected_wage_in_current_month = 1; }
			if(strcmp(buffer, "/expected_wage_in_current_month") == 0) { in_expected_wage_in_current_month = 0; }
			if(strcmp(buffer, "expected_wage_in_previous_month") == 0) { in_expected_wage_in_previous_month = 1; }
			if(strcmp(buffer, "/expected_wage_in_previous_month") == 0) { in_expected_wage_in_previous_month = 0; }
			if(strcmp(buffer, "expected_mean_specific_skills_in_current_month") == 0) { in_expected_mean_specific_skills_in_current_month = 1; }
			if(strcmp(buffer, "/expected_mean_specific_skills_in_current_month") == 0) { in_expected_mean_specific_skills_in_current_month = 0; }
			if(strcmp(buffer, "expected_mean_specific_skills_in_previous_month") == 0) { in_expected_mean_specific_skills_in_previous_month = 1; }
			if(strcmp(buffer, "/expected_mean_specific_skills_in_previous_month") == 0) { in_expected_mean_specific_skills_in_previous_month = 0; }
			if(strcmp(buffer, "expected_average_productivity_in_current_month") == 0) { in_expected_average_productivity_in_current_month = 1; }
			if(strcmp(buffer, "/expected_average_productivity_in_current_month") == 0) { in_expected_average_productivity_in_current_month = 0; }
			if(strcmp(buffer, "expected_investment_nominal_in_current_month") == 0) { in_expected_investment_nominal_in_current_month = 1; }
			if(strcmp(buffer, "/expected_investment_nominal_in_current_month") == 0) { in_expected_investment_nominal_in_current_month = 0; }
			if(strcmp(buffer, "expected_investment_nominal_in_previous_month") == 0) { in_expected_investment_nominal_in_previous_month = 1; }
			if(strcmp(buffer, "/expected_investment_nominal_in_previous_month") == 0) { in_expected_investment_nominal_in_previous_month = 0; }
			if(strcmp(buffer, "expected_average_productivity_in_previous_month") == 0) { in_expected_average_productivity_in_previous_month = 1; }
			if(strcmp(buffer, "/expected_average_productivity_in_previous_month") == 0) { in_expected_average_productivity_in_previous_month = 0; }
			if(strcmp(buffer, "earnings_while_last_pricing_period") == 0) { in_earnings_while_last_pricing_period = 1; }
			if(strcmp(buffer, "/earnings_while_last_pricing_period") == 0) { in_earnings_while_last_pricing_period = 0; }
			if(strcmp(buffer, "sum_earnings_since_price_change") == 0) { in_sum_earnings_since_price_change = 1; }
			if(strcmp(buffer, "/sum_earnings_since_price_change") == 0) { in_sum_earnings_since_price_change = 0; }
			if(strcmp(buffer, "variables_last_year") == 0) { in_variables_last_year = 1; }
			if(strcmp(buffer, "/variables_last_year") == 0) { in_variables_last_year = 0; }
			if(strcmp(buffer, "innovation_month_counter") == 0) { in_innovation_month_counter = 1; }
			if(strcmp(buffer, "/innovation_month_counter") == 0) { in_innovation_month_counter = 0; }
			if(strcmp(buffer, "variables_change") == 0) { in_variables_change = 1; }
			if(strcmp(buffer, "/variables_change") == 0) { in_variables_change = 0; }
			if(strcmp(buffer, "r_and_d_investments_per_month") == 0) { in_r_and_d_investments_per_month = 1; }
			if(strcmp(buffer, "/r_and_d_investments_per_month") == 0) { in_r_and_d_investments_per_month = 0; }
			if(strcmp(buffer, "innovation_flag") == 0) { in_innovation_flag = 1; }
			if(strcmp(buffer, "/innovation_flag") == 0) { in_innovation_flag = 0; }
			if(strcmp(buffer, "innovation_employees_needed") == 0) { in_innovation_employees_needed = 1; }
			if(strcmp(buffer, "/innovation_employees_needed") == 0) { in_innovation_employees_needed = 0; }
			if(strcmp(buffer, "no_employees_innovation") == 0) { in_no_employees_innovation = 1; }
			if(strcmp(buffer, "/no_employees_innovation") == 0) { in_no_employees_innovation = 0; }
			if(strcmp(buffer, "employees_needed_innovation") == 0) { in_employees_needed_innovation = 1; }
			if(strcmp(buffer, "/employees_needed_innovation") == 0) { in_employees_needed_innovation = 0; }
			if(strcmp(buffer, "optimal_employees_needed_innovation") == 0) { in_optimal_employees_needed_innovation = 1; }
			if(strcmp(buffer, "/optimal_employees_needed_innovation") == 0) { in_optimal_employees_needed_innovation = 0; }
			if(strcmp(buffer, "total_no_periods_for_product_development") == 0) { in_total_no_periods_for_product_development = 1; }
			if(strcmp(buffer, "/total_no_periods_for_product_development") == 0) { in_total_no_periods_for_product_development = 0; }
			if(strcmp(buffer, "ratio_project_value_established_product") == 0) { in_ratio_project_value_established_product = 1; }
			if(strcmp(buffer, "/ratio_project_value_established_product") == 0) { in_ratio_project_value_established_product = 0; }
			if(strcmp(buffer, "vintage_choice_already_taken") == 0) { in_vintage_choice_already_taken = 1; }
			if(strcmp(buffer, "/vintage_choice_already_taken") == 0) { in_vintage_choice_already_taken = 0; }
			if(strcmp(buffer, "change_due_to_last_innovation") == 0) { in_change_due_to_last_innovation = 1; }
			if(strcmp(buffer, "/change_due_to_last_innovation") == 0) { in_change_due_to_last_innovation = 0; }
			if(strcmp(buffer, "remaining_periods_to_complete_product_development") == 0) { in_remaining_periods_to_complete_product_development = 1; }
			if(strcmp(buffer, "/remaining_periods_to_complete_product_development") == 0) { in_remaining_periods_to_complete_product_development = 0; }
			if(strcmp(buffer, "planned_quality") == 0) { in_planned_quality = 1; }
			if(strcmp(buffer, "/planned_quality") == 0) { in_planned_quality = 0; }
			if(strcmp(buffer, "product_development_completed") == 0) { in_product_development_completed = 1; }
			if(strcmp(buffer, "/product_development_completed") == 0) { in_product_development_completed = 0; }
			if(strcmp(buffer, "price_just_set_flag") == 0) { in_price_just_set_flag = 1; }
			if(strcmp(buffer, "/price_just_set_flag") == 0) { in_price_just_set_flag = 0; }
			if(strcmp(buffer, "value_lattice") == 0) { in_value_lattice = 1; }
			if(strcmp(buffer, "/value_lattice") == 0) { in_value_lattice = 0; }
			if(strcmp(buffer, "combined_variance_demand_function") == 0) { in_combined_variance_demand_function = 1; }
			if(strcmp(buffer, "/combined_variance_demand_function") == 0) { in_combined_variance_demand_function = 0; }
			if(strcmp(buffer, "neighboring_region_ids") == 0) { in_neighboring_region_ids = 1; }
			if(strcmp(buffer, "/neighboring_region_ids") == 0) { in_neighboring_region_ids = 0; }
			if(strcmp(buffer, "consumption_budget") == 0) { in_consumption_budget = 1; }
			if(strcmp(buffer, "/consumption_budget") == 0) { in_consumption_budget = 0; }
			if(strcmp(buffer, "housing_budget") == 0) { in_housing_budget = 1; }
			if(strcmp(buffer, "/housing_budget") == 0) { in_housing_budget = 0; }
			if(strcmp(buffer, "consumption_budget_in_month") == 0) { in_consumption_budget_in_month = 1; }
			if(strcmp(buffer, "/consumption_budget_in_month") == 0) { in_consumption_budget_in_month = 0; }
			if(strcmp(buffer, "week_of_month") == 0) { in_week_of_month = 1; }
			if(strcmp(buffer, "/week_of_month") == 0) { in_week_of_month = 0; }
			if(strcmp(buffer, "weekly_budget") == 0) { in_weekly_budget = 1; }
			if(strcmp(buffer, "/weekly_budget") == 0) { in_weekly_budget = 0; }
			if(strcmp(buffer, "rationed") == 0) { in_rationed = 1; }
			if(strcmp(buffer, "/rationed") == 0) { in_rationed = 0; }
			if(strcmp(buffer, "mall_completely_sold_out") == 0) { in_mall_completely_sold_out = 1; }
			if(strcmp(buffer, "/mall_completely_sold_out") == 0) { in_mall_completely_sold_out = 0; }
			if(strcmp(buffer, "order_quantity") == 0) { in_order_quantity = 1; }
			if(strcmp(buffer, "/order_quantity") == 0) { in_order_quantity = 0; }
			if(strcmp(buffer, "received_quantity") == 0) { in_received_quantity = 1; }
			if(strcmp(buffer, "/received_quantity") == 0) { in_received_quantity = 0; }
			if(strcmp(buffer, "day_of_week_to_act") == 0) { in_day_of_week_to_act = 1; }
			if(strcmp(buffer, "/day_of_week_to_act") == 0) { in_day_of_week_to_act = 0; }
			if(strcmp(buffer, "day_of_month_receive_income") == 0) { in_day_of_month_receive_income = 1; }
			if(strcmp(buffer, "/day_of_month_receive_income") == 0) { in_day_of_month_receive_income = 0; }
			if(strcmp(buffer, "current_productivity_employer") == 0) { in_current_productivity_employer = 1; }
			if(strcmp(buffer, "/current_productivity_employer") == 0) { in_current_productivity_employer = 0; }
			if(strcmp(buffer, "current_mean_specific_skills_employer") == 0) { in_current_mean_specific_skills_employer = 1; }
			if(strcmp(buffer, "/current_mean_specific_skills_employer") == 0) { in_current_mean_specific_skills_employer = 0; }
			if(strcmp(buffer, "cum_total_dividends") == 0) { in_cum_total_dividends = 1; }
			if(strcmp(buffer, "/cum_total_dividends") == 0) { in_cum_total_dividends = 0; }
			if(strcmp(buffer, "tax_rate_hh_capital") == 0) { in_tax_rate_hh_capital = 1; }
			if(strcmp(buffer, "/tax_rate_hh_capital") == 0) { in_tax_rate_hh_capital = 0; }
			if(strcmp(buffer, "tax_rate_hh_labour") == 0) { in_tax_rate_hh_labour = 1; }
			if(strcmp(buffer, "/tax_rate_hh_labour") == 0) { in_tax_rate_hh_labour = 0; }
			if(strcmp(buffer, "price_index") == 0) { in_price_index = 1; }
			if(strcmp(buffer, "/price_index") == 0) { in_price_index = 0; }
			if(strcmp(buffer, "price_index_base_period") == 0) { in_price_index_base_period = 1; }
			if(strcmp(buffer, "/price_index_base_period") == 0) { in_price_index_base_period = 0; }
			if(strcmp(buffer, "commuting_costs_price_level_weight") == 0) { in_commuting_costs_price_level_weight = 1; }
			if(strcmp(buffer, "/commuting_costs_price_level_weight") == 0) { in_commuting_costs_price_level_weight = 0; }
			if(strcmp(buffer, "expenditures") == 0) { in_expenditures = 1; }
			if(strcmp(buffer, "/expenditures") == 0) { in_expenditures = 0; }
			if(strcmp(buffer, "received_dividend") == 0) { in_received_dividend = 1; }
			if(strcmp(buffer, "/received_dividend") == 0) { in_received_dividend = 0; }
			if(strcmp(buffer, "received_dividend_in_calendar_month") == 0) { in_received_dividend_in_calendar_month = 1; }
			if(strcmp(buffer, "/received_dividend_in_calendar_month") == 0) { in_received_dividend_in_calendar_month = 0; }
			if(strcmp(buffer, "flag_consumption_shifting") == 0) { in_flag_consumption_shifting = 1; }
			if(strcmp(buffer, "/flag_consumption_shifting") == 0) { in_flag_consumption_shifting = 0; }
			if(strcmp(buffer, "excess_weekly_budget") == 0) { in_excess_weekly_budget = 1; }
			if(strcmp(buffer, "/excess_weekly_budget") == 0) { in_excess_weekly_budget = 0; }
			if(strcmp(buffer, "wealth_income_ratio_actual") == 0) { in_wealth_income_ratio_actual = 1; }
			if(strcmp(buffer, "/wealth_income_ratio_actual") == 0) { in_wealth_income_ratio_actual = 0; }
			if(strcmp(buffer, "wealth_income_ratio_target") == 0) { in_wealth_income_ratio_target = 1; }
			if(strcmp(buffer, "/wealth_income_ratio_target") == 0) { in_wealth_income_ratio_target = 0; }
			if(strcmp(buffer, "last_weekly_budget") == 0) { in_last_weekly_budget = 1; }
			if(strcmp(buffer, "/last_weekly_budget") == 0) { in_last_weekly_budget = 0; }
			if(strcmp(buffer, "have_mortgage") == 0) { in_have_mortgage = 1; }
			if(strcmp(buffer, "/have_mortgage") == 0) { in_have_mortgage = 0; }
			if(strcmp(buffer, "hmr_mortgage_status") == 0) { in_hmr_mortgage_status = 1; }
			if(strcmp(buffer, "/hmr_mortgage_status") == 0) { in_hmr_mortgage_status = 0; }
			if(strcmp(buffer, "op_mortgage_status") == 0) { in_op_mortgage_status = 1; }
			if(strcmp(buffer, "/op_mortgage_status") == 0) { in_op_mortgage_status = 0; }
			if(strcmp(buffer, "request_mortgage") == 0) { in_request_mortgage = 1; }
			if(strcmp(buffer, "/request_mortgage") == 0) { in_request_mortgage = 0; }
			if(strcmp(buffer, "mortgage_pay_day") == 0) { in_mortgage_pay_day = 1; }
			if(strcmp(buffer, "/mortgage_pay_day") == 0) { in_mortgage_pay_day = 0; }
			if(strcmp(buffer, "mortgage_sample_inputs") == 0) { in_mortgage_sample_inputs = 1; }
			if(strcmp(buffer, "/mortgage_sample_inputs") == 0) { in_mortgage_sample_inputs = 0; }
			if(strcmp(buffer, "sample_inputs") == 0) { in_sample_inputs = 1; }
			if(strcmp(buffer, "/sample_inputs") == 0) { in_sample_inputs = 0; }
			if(strcmp(buffer, "is_tenant") == 0) { in_is_tenant = 1; }
			if(strcmp(buffer, "/is_tenant") == 0) { in_is_tenant = 0; }
			if(strcmp(buffer, "is_owner") == 0) { in_is_owner = 1; }
			if(strcmp(buffer, "/is_owner") == 0) { in_is_owner = 0; }
			if(strcmp(buffer, "is_landlord") == 0) { in_is_landlord = 1; }
			if(strcmp(buffer, "/is_landlord") == 0) { in_is_landlord = 0; }
			if(strcmp(buffer, "plan_stay_tenant") == 0) { in_plan_stay_tenant = 1; }
			if(strcmp(buffer, "/plan_stay_tenant") == 0) { in_plan_stay_tenant = 0; }
			if(strcmp(buffer, "plan_stay_owner") == 0) { in_plan_stay_owner = 1; }
			if(strcmp(buffer, "/plan_stay_owner") == 0) { in_plan_stay_owner = 0; }
			if(strcmp(buffer, "plan_stay_landlord") == 0) { in_plan_stay_landlord = 1; }
			if(strcmp(buffer, "/plan_stay_landlord") == 0) { in_plan_stay_landlord = 0; }
			if(strcmp(buffer, "plan_sell_hmr") == 0) { in_plan_sell_hmr = 1; }
			if(strcmp(buffer, "/plan_sell_hmr") == 0) { in_plan_sell_hmr = 0; }
			if(strcmp(buffer, "plan_buy_hmr") == 0) { in_plan_buy_hmr = 1; }
			if(strcmp(buffer, "/plan_buy_hmr") == 0) { in_plan_buy_hmr = 0; }
			if(strcmp(buffer, "plan_rent_hmr") == 0) { in_plan_rent_hmr = 1; }
			if(strcmp(buffer, "/plan_rent_hmr") == 0) { in_plan_rent_hmr = 0; }
			if(strcmp(buffer, "plan_stop_rent_hmr") == 0) { in_plan_stop_rent_hmr = 1; }
			if(strcmp(buffer, "/plan_stop_rent_hmr") == 0) { in_plan_stop_rent_hmr = 0; }
			if(strcmp(buffer, "plan_buy_op") == 0) { in_plan_buy_op = 1; }
			if(strcmp(buffer, "/plan_buy_op") == 0) { in_plan_buy_op = 0; }
			if(strcmp(buffer, "plan_sell_op") == 0) { in_plan_sell_op = 1; }
			if(strcmp(buffer, "/plan_sell_op") == 0) { in_plan_sell_op = 0; }
			if(strcmp(buffer, "plan_let_op") == 0) { in_plan_let_op = 1; }
			if(strcmp(buffer, "/plan_let_op") == 0) { in_plan_let_op = 0; }
			if(strcmp(buffer, "plan_stop_let_op") == 0) { in_plan_stop_let_op = 1; }
			if(strcmp(buffer, "/plan_stop_let_op") == 0) { in_plan_stop_let_op = 0; }
			if(strcmp(buffer, "just_sold_hmr") == 0) { in_just_sold_hmr = 1; }
			if(strcmp(buffer, "/just_sold_hmr") == 0) { in_just_sold_hmr = 0; }
			if(strcmp(buffer, "just_purchased_hmr") == 0) { in_just_purchased_hmr = 1; }
			if(strcmp(buffer, "/just_purchased_hmr") == 0) { in_just_purchased_hmr = 0; }
			if(strcmp(buffer, "just_purchased_op") == 0) { in_just_purchased_op = 1; }
			if(strcmp(buffer, "/just_purchased_op") == 0) { in_just_purchased_op = 0; }
			if(strcmp(buffer, "just_sold_op") == 0) { in_just_sold_op = 1; }
			if(strcmp(buffer, "/just_sold_op") == 0) { in_just_sold_op = 0; }
			if(strcmp(buffer, "else_state") == 0) { in_else_state = 1; }
			if(strcmp(buffer, "/else_state") == 0) { in_else_state = 0; }
			if(strcmp(buffer, "other_states") == 0) { in_other_states = 1; }
			if(strcmp(buffer, "/other_states") == 0) { in_other_states = 0; }
			if(strcmp(buffer, "total_dsti") == 0) { in_total_dsti = 1; }
			if(strcmp(buffer, "/total_dsti") == 0) { in_total_dsti = 0; }
			if(strcmp(buffer, "rental_unit") == 0) { in_rental_unit = 1; }
			if(strcmp(buffer, "/rental_unit") == 0) { in_rental_unit = 0; }
			if(strcmp(buffer, "risk_free_rate") == 0) { in_risk_free_rate = 1; }
			if(strcmp(buffer, "/risk_free_rate") == 0) { in_risk_free_rate = 0; }
			if(strcmp(buffer, "wealth") == 0) { in_wealth = 1; }
			if(strcmp(buffer, "/wealth") == 0) { in_wealth = 0; }
			if(strcmp(buffer, "beliefs") == 0) { in_beliefs = 1; }
			if(strcmp(buffer, "/beliefs") == 0) { in_beliefs = 0; }
			if(strcmp(buffer, "assetsowned") == 0) { in_assetsowned = 1; }
			if(strcmp(buffer, "/assetsowned") == 0) { in_assetsowned = 0; }
			if(strcmp(buffer, "logit_beta") == 0) { in_logit_beta = 1; }
			if(strcmp(buffer, "/logit_beta") == 0) { in_logit_beta = 0; }
			if(strcmp(buffer, "wage") == 0) { in_wage = 1; }
			if(strcmp(buffer, "/wage") == 0) { in_wage = 0; }
			if(strcmp(buffer, "wage_reservation") == 0) { in_wage_reservation = 1; }
			if(strcmp(buffer, "/wage_reservation") == 0) { in_wage_reservation = 0; }
			if(strcmp(buffer, "general_skill") == 0) { in_general_skill = 1; }
			if(strcmp(buffer, "/general_skill") == 0) { in_general_skill = 0; }
			if(strcmp(buffer, "list_adaptation_speed_per_general_skill_group") == 0) { in_list_adaptation_speed_per_general_skill_group = 1; }
			if(strcmp(buffer, "/list_adaptation_speed_per_general_skill_group") == 0) { in_list_adaptation_speed_per_general_skill_group = 0; }
			if(strcmp(buffer, "on_the_job_search") == 0) { in_on_the_job_search = 1; }
			if(strcmp(buffer, "/on_the_job_search") == 0) { in_on_the_job_search = 0; }
			if(strcmp(buffer, "search_today") == 0) { in_search_today = 1; }
			if(strcmp(buffer, "/search_today") == 0) { in_search_today = 0; }
			if(strcmp(buffer, "last_labour_income") == 0) { in_last_labour_income = 1; }
			if(strcmp(buffer, "/last_labour_income") == 0) { in_last_labour_income = 0; }
			if(strcmp(buffer, "specific_skill") == 0) { in_specific_skill = 1; }
			if(strcmp(buffer, "/specific_skill") == 0) { in_specific_skill = 0; }
			if(strcmp(buffer, "employee_firm_id") == 0) { in_employee_firm_id = 1; }
			if(strcmp(buffer, "/employee_firm_id") == 0) { in_employee_firm_id = 0; }
			if(strcmp(buffer, "just_employed") == 0) { in_just_employed = 1; }
			if(strcmp(buffer, "/just_employed") == 0) { in_just_employed = 0; }
			if(strcmp(buffer, "just_unemployed") == 0) { in_just_unemployed = 1; }
			if(strcmp(buffer, "/just_unemployed") == 0) { in_just_unemployed = 0; }
			if(strcmp(buffer, "start_unemployed") == 0) { in_start_unemployed = 1; }
			if(strcmp(buffer, "/start_unemployed") == 0) { in_start_unemployed = 0; }
			if(strcmp(buffer, "start_employed") == 0) { in_start_employed = 1; }
			if(strcmp(buffer, "/start_employed") == 0) { in_start_employed = 0; }
			if(strcmp(buffer, "unemployed_duration") == 0) { in_unemployed_duration = 1; }
			if(strcmp(buffer, "/unemployed_duration") == 0) { in_unemployed_duration = 0; }
			if(strcmp(buffer, "enter_matching") == 0) { in_enter_matching = 1; }
			if(strcmp(buffer, "/enter_matching") == 0) { in_enter_matching = 0; }
			if(strcmp(buffer, "employer_region_id") == 0) { in_employer_region_id = 1; }
			if(strcmp(buffer, "/employer_region_id") == 0) { in_employer_region_id = 0; }
			if(strcmp(buffer, "employer_igfirm") == 0) { in_employer_igfirm = 1; }
			if(strcmp(buffer, "/employer_igfirm") == 0) { in_employer_igfirm = 0; }
			if(strcmp(buffer, "day_of_month_receive_benefit") == 0) { in_day_of_month_receive_benefit = 1; }
			if(strcmp(buffer, "/day_of_month_receive_benefit") == 0) { in_day_of_month_receive_benefit = 0; }
			if(strcmp(buffer, "unemployment_payment") == 0) { in_unemployment_payment = 1; }
			if(strcmp(buffer, "/unemployment_payment") == 0) { in_unemployment_payment = 0; }
			if(strcmp(buffer, "region_wide_mean_wage") == 0) { in_region_wide_mean_wage = 1; }
			if(strcmp(buffer, "/region_wide_mean_wage") == 0) { in_region_wide_mean_wage = 0; }
			if(strcmp(buffer, "last_net_income") == 0) { in_last_net_income = 1; }
			if(strcmp(buffer, "/last_net_income") == 0) { in_last_net_income = 0; }
			if(strcmp(buffer, "mean_net_income") == 0) { in_mean_net_income = 1; }
			if(strcmp(buffer, "/mean_net_income") == 0) { in_mean_net_income = 0; }
			if(strcmp(buffer, "monthly_income_vector") == 0) { in_monthly_income_vector = 1; }
			if(strcmp(buffer, "/monthly_income_vector") == 0) { in_monthly_income_vector = 0; }
			if(strcmp(buffer, "quarterly_income_vector") == 0) { in_quarterly_income_vector = 1; }
			if(strcmp(buffer, "/quarterly_income_vector") == 0) { in_quarterly_income_vector = 0; }
			if(strcmp(buffer, "total_gross_monthly_income") == 0) { in_total_gross_monthly_income = 1; }
			if(strcmp(buffer, "/total_gross_monthly_income") == 0) { in_total_gross_monthly_income = 0; }
			if(strcmp(buffer, "total_gross_quarterly_income") == 0) { in_total_gross_quarterly_income = 1; }
			if(strcmp(buffer, "/total_gross_quarterly_income") == 0) { in_total_gross_quarterly_income = 0; }
			if(strcmp(buffer, "household_balance_sheet_calendar") == 0) { in_household_balance_sheet_calendar = 1; }
			if(strcmp(buffer, "/household_balance_sheet_calendar") == 0) { in_household_balance_sheet_calendar = 0; }
			if(strcmp(buffer, "household_stocks_calendar") == 0) { in_household_stocks_calendar = 1; }
			if(strcmp(buffer, "/household_stocks_calendar") == 0) { in_household_stocks_calendar = 0; }
			if(strcmp(buffer, "household_outflows_calendar") == 0) { in_household_outflows_calendar = 1; }
			if(strcmp(buffer, "/household_outflows_calendar") == 0) { in_household_outflows_calendar = 0; }
			if(strcmp(buffer, "household_inflows_calendar") == 0) { in_household_inflows_calendar = 1; }
			if(strcmp(buffer, "/household_inflows_calendar") == 0) { in_household_inflows_calendar = 0; }
			if(strcmp(buffer, "unemployment_benefit_pct") == 0) { in_unemployment_benefit_pct = 1; }
			if(strcmp(buffer, "/unemployment_benefit_pct") == 0) { in_unemployment_benefit_pct = 0; }
			if(strcmp(buffer, "monthly_consumption_expenditure") == 0) { in_monthly_consumption_expenditure = 1; }
			if(strcmp(buffer, "/monthly_consumption_expenditure") == 0) { in_monthly_consumption_expenditure = 0; }
			if(strcmp(buffer, "monthly_bond_interest_income") == 0) { in_monthly_bond_interest_income = 1; }
			if(strcmp(buffer, "/monthly_bond_interest_income") == 0) { in_monthly_bond_interest_income = 0; }
			if(strcmp(buffer, "region_mean_wage") == 0) { in_region_mean_wage = 1; }
			if(strcmp(buffer, "/region_mean_wage") == 0) { in_region_mean_wage = 0; }
			if(strcmp(buffer, "human_capital_policy_flag") == 0) { in_human_capital_policy_flag = 1; }
			if(strcmp(buffer, "/human_capital_policy_flag") == 0) { in_human_capital_policy_flag = 0; }
			if(strcmp(buffer, "questionnaire_attending_propability") == 0) { in_questionnaire_attending_propability = 1; }
			if(strcmp(buffer, "/questionnaire_attending_propability") == 0) { in_questionnaire_attending_propability = 0; }
			if(strcmp(buffer, "willingness_to_attend") == 0) { in_willingness_to_attend = 1; }
			if(strcmp(buffer, "/willingness_to_attend") == 0) { in_willingness_to_attend = 0; }
			if(strcmp(buffer, "interviewer_id") == 0) { in_interviewer_id = 1; }
			if(strcmp(buffer, "/interviewer_id") == 0) { in_interviewer_id = 0; }
			if(strcmp(buffer, "random_no_test") == 0) { in_random_no_test = 1; }
			if(strcmp(buffer, "/random_no_test") == 0) { in_random_no_test = 0; }
			if(strcmp(buffer, "questionnaire") == 0) { in_questionnaire = 1; }
			if(strcmp(buffer, "/questionnaire") == 0) { in_questionnaire = 0; }
			if(strcmp(buffer, "current_price_quality_list") == 0) { in_current_price_quality_list = 1; }
			if(strcmp(buffer, "/current_price_quality_list") == 0) { in_current_price_quality_list = 0; }
			if(strcmp(buffer, "housing_bid_price") == 0) { in_housing_bid_price = 1; }
			if(strcmp(buffer, "/housing_bid_price") == 0) { in_housing_bid_price = 0; }
			if(strcmp(buffer, "housing_ask_price") == 0) { in_housing_ask_price = 1; }
			if(strcmp(buffer, "/housing_ask_price") == 0) { in_housing_ask_price = 0; }
			if(strcmp(buffer, "house") == 0) { in_house = 1; }
			if(strcmp(buffer, "/house") == 0) { in_house = 0; }
			if(strcmp(buffer, "rent_bid_price") == 0) { in_rent_bid_price = 1; }
			if(strcmp(buffer, "/rent_bid_price") == 0) { in_rent_bid_price = 0; }
			if(strcmp(buffer, "rent_ask_price") == 0) { in_rent_ask_price = 1; }
			if(strcmp(buffer, "/rent_ask_price") == 0) { in_rent_ask_price = 0; }
			if(strcmp(buffer, "hmr_price_index") == 0) { in_hmr_price_index = 1; }
			if(strcmp(buffer, "/hmr_price_index") == 0) { in_hmr_price_index = 0; }
			if(strcmp(buffer, "op_price_index") == 0) { in_op_price_index = 1; }
			if(strcmp(buffer, "/op_price_index") == 0) { in_op_price_index = 0; }
			if(strcmp(buffer, "rent_price_index") == 0) { in_rent_price_index = 1; }
			if(strcmp(buffer, "/rent_price_index") == 0) { in_rent_price_index = 0; }
			if(strcmp(buffer, "current_stock") == 0) { in_current_stock = 1; }
			if(strcmp(buffer, "/current_stock") == 0) { in_current_stock = 0; }
			if(strcmp(buffer, "firm_revenues") == 0) { in_firm_revenues = 1; }
			if(strcmp(buffer, "/firm_revenues") == 0) { in_firm_revenues = 0; }
			if(strcmp(buffer, "productivity") == 0) { in_productivity = 1; }
			if(strcmp(buffer, "/productivity") == 0) { in_productivity = 0; }
			if(strcmp(buffer, "capital_good_price") == 0) { in_capital_good_price = 1; }
			if(strcmp(buffer, "/capital_good_price") == 0) { in_capital_good_price = 0; }
			if(strcmp(buffer, "vintages") == 0) { in_vintages = 1; }
			if(strcmp(buffer, "/vintages") == 0) { in_vintages = 0; }
			if(strcmp(buffer, "sales_per_vintage") == 0) { in_sales_per_vintage = 1; }
			if(strcmp(buffer, "/sales_per_vintage") == 0) { in_sales_per_vintage = 0; }
			if(strcmp(buffer, "mean_productivity_of_sales") == 0) { in_mean_productivity_of_sales = 1; }
			if(strcmp(buffer, "/mean_productivity_of_sales") == 0) { in_mean_productivity_of_sales = 0; }
			if(strcmp(buffer, "ratio_sold_productivity_best_practice") == 0) { in_ratio_sold_productivity_best_practice = 1; }
			if(strcmp(buffer, "/ratio_sold_productivity_best_practice") == 0) { in_ratio_sold_productivity_best_practice = 0; }
			if(strcmp(buffer, "igfirm_endogenous_innovation_probability") == 0) { in_igfirm_endogenous_innovation_probability = 1; }
			if(strcmp(buffer, "/igfirm_endogenous_innovation_probability") == 0) { in_igfirm_endogenous_innovation_probability = 0; }
			if(strcmp(buffer, "net_profit") == 0) { in_net_profit = 1; }
			if(strcmp(buffer, "/net_profit") == 0) { in_net_profit = 0; }
			if(strcmp(buffer, "energy_price_markup") == 0) { in_energy_price_markup = 1; }
			if(strcmp(buffer, "/energy_price_markup") == 0) { in_energy_price_markup = 0; }
			if(strcmp(buffer, "energy_costs_per_day") == 0) { in_energy_costs_per_day = 1; }
			if(strcmp(buffer, "/energy_costs_per_day") == 0) { in_energy_costs_per_day = 0; }
			if(strcmp(buffer, "earnings_per_day") == 0) { in_earnings_per_day = 1; }
			if(strcmp(buffer, "/earnings_per_day") == 0) { in_earnings_per_day = 0; }
			if(strcmp(buffer, "cum_energy_costs") == 0) { in_cum_energy_costs = 1; }
			if(strcmp(buffer, "/cum_energy_costs") == 0) { in_cum_energy_costs = 0; }
			if(strcmp(buffer, "last_net_profits") == 0) { in_last_net_profits = 1; }
			if(strcmp(buffer, "/last_net_profits") == 0) { in_last_net_profits = 0; }
			if(strcmp(buffer, "mean_sales_last_months") == 0) { in_mean_sales_last_months = 1; }
			if(strcmp(buffer, "/mean_sales_last_months") == 0) { in_mean_sales_last_months = 0; }
			if(strcmp(buffer, "last_sales") == 0) { in_last_sales = 1; }
			if(strcmp(buffer, "/last_sales") == 0) { in_last_sales = 0; }
			if(strcmp(buffer, "dividend_payment") == 0) { in_dividend_payment = 1; }
			if(strcmp(buffer, "/dividend_payment") == 0) { in_dividend_payment = 0; }
			if(strcmp(buffer, "duration_until_next_innovation") == 0) { in_duration_until_next_innovation = 1; }
			if(strcmp(buffer, "/duration_until_next_innovation") == 0) { in_duration_until_next_innovation = 0; }
			if(strcmp(buffer, "sales") == 0) { in_sales = 1; }
			if(strcmp(buffer, "/sales") == 0) { in_sales = 0; }
			if(strcmp(buffer, "capital_good_demand") == 0) { in_capital_good_demand = 1; }
			if(strcmp(buffer, "/capital_good_demand") == 0) { in_capital_good_demand = 0; }
			if(strcmp(buffer, "capital_good_demand_last_month") == 0) { in_capital_good_demand_last_month = 1; }
			if(strcmp(buffer, "/capital_good_demand_last_month") == 0) { in_capital_good_demand_last_month = 0; }
			if(strcmp(buffer, "sales_last_month") == 0) { in_sales_last_month = 1; }
			if(strcmp(buffer, "/sales_last_month") == 0) { in_sales_last_month = 0; }
			if(strcmp(buffer, "cum_revenue_last_month") == 0) { in_cum_revenue_last_month = 1; }
			if(strcmp(buffer, "/cum_revenue_last_month") == 0) { in_cum_revenue_last_month = 0; }
			if(strcmp(buffer, "innovation_sheme_low_progress") == 0) { in_innovation_sheme_low_progress = 1; }
			if(strcmp(buffer, "/innovation_sheme_low_progress") == 0) { in_innovation_sheme_low_progress = 0; }
			if(strcmp(buffer, "innovation_sheme_medium_progress") == 0) { in_innovation_sheme_medium_progress = 1; }
			if(strcmp(buffer, "/innovation_sheme_medium_progress") == 0) { in_innovation_sheme_medium_progress = 0; }
			if(strcmp(buffer, "innovation_sheme_high_progress") == 0) { in_innovation_sheme_high_progress = 1; }
			if(strcmp(buffer, "/innovation_sheme_high_progress") == 0) { in_innovation_sheme_high_progress = 0; }
			if(strcmp(buffer, "mean_general_skills") == 0) { in_mean_general_skills = 1; }
			if(strcmp(buffer, "/mean_general_skills") == 0) { in_mean_general_skills = 0; }
			if(strcmp(buffer, "mean_adaptation_speed") == 0) { in_mean_adaptation_speed = 1; }
			if(strcmp(buffer, "/mean_adaptation_speed") == 0) { in_mean_adaptation_speed = 0; }
			if(strcmp(buffer, "productivity_progress_in_economy") == 0) { in_productivity_progress_in_economy = 1; }
			if(strcmp(buffer, "/productivity_progress_in_economy") == 0) { in_productivity_progress_in_economy = 0; }
			if(strcmp(buffer, "economy_wide_capital_stock") == 0) { in_economy_wide_capital_stock = 1; }
			if(strcmp(buffer, "/economy_wide_capital_stock") == 0) { in_economy_wide_capital_stock = 0; }
			if(strcmp(buffer, "list_adaptation_speed") == 0) { in_list_adaptation_speed = 1; }
			if(strcmp(buffer, "/list_adaptation_speed") == 0) { in_list_adaptation_speed = 0; }
			if(strcmp(buffer, "igfirm_balance_sheet_calendar") == 0) { in_igfirm_balance_sheet_calendar = 1; }
			if(strcmp(buffer, "/igfirm_balance_sheet_calendar") == 0) { in_igfirm_balance_sheet_calendar = 0; }
			if(strcmp(buffer, "igfirm_stocks_calendar") == 0) { in_igfirm_stocks_calendar = 1; }
			if(strcmp(buffer, "/igfirm_stocks_calendar") == 0) { in_igfirm_stocks_calendar = 0; }
			if(strcmp(buffer, "igfirm_outflows_calendar") == 0) { in_igfirm_outflows_calendar = 1; }
			if(strcmp(buffer, "/igfirm_outflows_calendar") == 0) { in_igfirm_outflows_calendar = 0; }
			if(strcmp(buffer, "igfirm_inflows_calendar") == 0) { in_igfirm_inflows_calendar = 1; }
			if(strcmp(buffer, "/igfirm_inflows_calendar") == 0) { in_igfirm_inflows_calendar = 0; }
			if(strcmp(buffer, "economy_wide_general_skills_in_firms") == 0) { in_economy_wide_general_skills_in_firms = 1; }
			if(strcmp(buffer, "/economy_wide_general_skills_in_firms") == 0) { in_economy_wide_general_skills_in_firms = 0; }
			if(strcmp(buffer, "economy_wide_specific_skills_in_firms") == 0) { in_economy_wide_specific_skills_in_firms = 1; }
			if(strcmp(buffer, "/economy_wide_specific_skills_in_firms") == 0) { in_economy_wide_specific_skills_in_firms = 0; }
			if(strcmp(buffer, "switch_datastorage") == 0) { in_switch_datastorage = 1; }
			if(strcmp(buffer, "/switch_datastorage") == 0) { in_switch_datastorage = 0; }
			if(strcmp(buffer, "num_households") == 0) { in_num_households = 1; }
			if(strcmp(buffer, "/num_households") == 0) { in_num_households = 0; }
			if(strcmp(buffer, "no_households_skill_1") == 0) { in_no_households_skill_1 = 1; }
			if(strcmp(buffer, "/no_households_skill_1") == 0) { in_no_households_skill_1 = 0; }
			if(strcmp(buffer, "no_households_skill_2") == 0) { in_no_households_skill_2 = 1; }
			if(strcmp(buffer, "/no_households_skill_2") == 0) { in_no_households_skill_2 = 0; }
			if(strcmp(buffer, "no_households_skill_3") == 0) { in_no_households_skill_3 = 1; }
			if(strcmp(buffer, "/no_households_skill_3") == 0) { in_no_households_skill_3 = 0; }
			if(strcmp(buffer, "no_households_skill_4") == 0) { in_no_households_skill_4 = 1; }
			if(strcmp(buffer, "/no_households_skill_4") == 0) { in_no_households_skill_4 = 0; }
			if(strcmp(buffer, "no_households_skill_5") == 0) { in_no_households_skill_5 = 1; }
			if(strcmp(buffer, "/no_households_skill_5") == 0) { in_no_households_skill_5 = 0; }
			if(strcmp(buffer, "employed") == 0) { in_employed = 1; }
			if(strcmp(buffer, "/employed") == 0) { in_employed = 0; }
			if(strcmp(buffer, "employed_skill_1") == 0) { in_employed_skill_1 = 1; }
			if(strcmp(buffer, "/employed_skill_1") == 0) { in_employed_skill_1 = 0; }
			if(strcmp(buffer, "employed_skill_2") == 0) { in_employed_skill_2 = 1; }
			if(strcmp(buffer, "/employed_skill_2") == 0) { in_employed_skill_2 = 0; }
			if(strcmp(buffer, "employed_skill_3") == 0) { in_employed_skill_3 = 1; }
			if(strcmp(buffer, "/employed_skill_3") == 0) { in_employed_skill_3 = 0; }
			if(strcmp(buffer, "employed_skill_4") == 0) { in_employed_skill_4 = 1; }
			if(strcmp(buffer, "/employed_skill_4") == 0) { in_employed_skill_4 = 0; }
			if(strcmp(buffer, "employed_skill_5") == 0) { in_employed_skill_5 = 1; }
			if(strcmp(buffer, "/employed_skill_5") == 0) { in_employed_skill_5 = 0; }
			if(strcmp(buffer, "unemployed") == 0) { in_unemployed = 1; }
			if(strcmp(buffer, "/unemployed") == 0) { in_unemployed = 0; }
			if(strcmp(buffer, "unemployment_rate") == 0) { in_unemployment_rate = 1; }
			if(strcmp(buffer, "/unemployment_rate") == 0) { in_unemployment_rate = 0; }
			if(strcmp(buffer, "employment_rate") == 0) { in_employment_rate = 1; }
			if(strcmp(buffer, "/employment_rate") == 0) { in_employment_rate = 0; }
			if(strcmp(buffer, "unemployment_rate_skill_1") == 0) { in_unemployment_rate_skill_1 = 1; }
			if(strcmp(buffer, "/unemployment_rate_skill_1") == 0) { in_unemployment_rate_skill_1 = 0; }
			if(strcmp(buffer, "unemployment_rate_skill_2") == 0) { in_unemployment_rate_skill_2 = 1; }
			if(strcmp(buffer, "/unemployment_rate_skill_2") == 0) { in_unemployment_rate_skill_2 = 0; }
			if(strcmp(buffer, "unemployment_rate_skill_3") == 0) { in_unemployment_rate_skill_3 = 1; }
			if(strcmp(buffer, "/unemployment_rate_skill_3") == 0) { in_unemployment_rate_skill_3 = 0; }
			if(strcmp(buffer, "unemployment_rate_skill_4") == 0) { in_unemployment_rate_skill_4 = 1; }
			if(strcmp(buffer, "/unemployment_rate_skill_4") == 0) { in_unemployment_rate_skill_4 = 0; }
			if(strcmp(buffer, "unemployment_rate_skill_5") == 0) { in_unemployment_rate_skill_5 = 1; }
			if(strcmp(buffer, "/unemployment_rate_skill_5") == 0) { in_unemployment_rate_skill_5 = 0; }
			if(strcmp(buffer, "average_wage") == 0) { in_average_wage = 1; }
			if(strcmp(buffer, "/average_wage") == 0) { in_average_wage = 0; }
			if(strcmp(buffer, "average_wage_skill_1") == 0) { in_average_wage_skill_1 = 1; }
			if(strcmp(buffer, "/average_wage_skill_1") == 0) { in_average_wage_skill_1 = 0; }
			if(strcmp(buffer, "average_wage_skill_2") == 0) { in_average_wage_skill_2 = 1; }
			if(strcmp(buffer, "/average_wage_skill_2") == 0) { in_average_wage_skill_2 = 0; }
			if(strcmp(buffer, "average_wage_skill_3") == 0) { in_average_wage_skill_3 = 1; }
			if(strcmp(buffer, "/average_wage_skill_3") == 0) { in_average_wage_skill_3 = 0; }
			if(strcmp(buffer, "average_wage_skill_4") == 0) { in_average_wage_skill_4 = 1; }
			if(strcmp(buffer, "/average_wage_skill_4") == 0) { in_average_wage_skill_4 = 0; }
			if(strcmp(buffer, "average_wage_skill_5") == 0) { in_average_wage_skill_5 = 1; }
			if(strcmp(buffer, "/average_wage_skill_5") == 0) { in_average_wage_skill_5 = 0; }
			if(strcmp(buffer, "average_s_skill") == 0) { in_average_s_skill = 1; }
			if(strcmp(buffer, "/average_s_skill") == 0) { in_average_s_skill = 0; }
			if(strcmp(buffer, "average_s_skill_1") == 0) { in_average_s_skill_1 = 1; }
			if(strcmp(buffer, "/average_s_skill_1") == 0) { in_average_s_skill_1 = 0; }
			if(strcmp(buffer, "average_s_skill_2") == 0) { in_average_s_skill_2 = 1; }
			if(strcmp(buffer, "/average_s_skill_2") == 0) { in_average_s_skill_2 = 0; }
			if(strcmp(buffer, "average_s_skill_3") == 0) { in_average_s_skill_3 = 1; }
			if(strcmp(buffer, "/average_s_skill_3") == 0) { in_average_s_skill_3 = 0; }
			if(strcmp(buffer, "average_s_skill_4") == 0) { in_average_s_skill_4 = 1; }
			if(strcmp(buffer, "/average_s_skill_4") == 0) { in_average_s_skill_4 = 0; }
			if(strcmp(buffer, "average_s_skill_5") == 0) { in_average_s_skill_5 = 1; }
			if(strcmp(buffer, "/average_s_skill_5") == 0) { in_average_s_skill_5 = 0; }
			if(strcmp(buffer, "total_consumption_budget") == 0) { in_total_consumption_budget = 1; }
			if(strcmp(buffer, "/total_consumption_budget") == 0) { in_total_consumption_budget = 0; }
			if(strcmp(buffer, "no_firms") == 0) { in_no_firms = 1; }
			if(strcmp(buffer, "/no_firms") == 0) { in_no_firms = 0; }
			if(strcmp(buffer, "no_active_firms") == 0) { in_no_active_firms = 1; }
			if(strcmp(buffer, "/no_active_firms") == 0) { in_no_active_firms = 0; }
			if(strcmp(buffer, "no_vacancies") == 0) { in_no_vacancies = 1; }
			if(strcmp(buffer, "/no_vacancies") == 0) { in_no_vacancies = 0; }
			if(strcmp(buffer, "no_posted_vacancies") == 0) { in_no_posted_vacancies = 1; }
			if(strcmp(buffer, "/no_posted_vacancies") == 0) { in_no_posted_vacancies = 0; }
			if(strcmp(buffer, "no_employees_r_and_d") == 0) { in_no_employees_r_and_d = 1; }
			if(strcmp(buffer, "/no_employees_r_and_d") == 0) { in_no_employees_r_and_d = 0; }
			if(strcmp(buffer, "firm_average_wage") == 0) { in_firm_average_wage = 1; }
			if(strcmp(buffer, "/firm_average_wage") == 0) { in_firm_average_wage = 0; }
			if(strcmp(buffer, "firm_average_production_wage") == 0) { in_firm_average_production_wage = 1; }
			if(strcmp(buffer, "/firm_average_production_wage") == 0) { in_firm_average_production_wage = 0; }
			if(strcmp(buffer, "firm_average_r_and_d_wage") == 0) { in_firm_average_r_and_d_wage = 1; }
			if(strcmp(buffer, "/firm_average_r_and_d_wage") == 0) { in_firm_average_r_and_d_wage = 0; }
			if(strcmp(buffer, "firm_average_wage_skill_1") == 0) { in_firm_average_wage_skill_1 = 1; }
			if(strcmp(buffer, "/firm_average_wage_skill_1") == 0) { in_firm_average_wage_skill_1 = 0; }
			if(strcmp(buffer, "firm_average_wage_skill_2") == 0) { in_firm_average_wage_skill_2 = 1; }
			if(strcmp(buffer, "/firm_average_wage_skill_2") == 0) { in_firm_average_wage_skill_2 = 0; }
			if(strcmp(buffer, "firm_average_wage_skill_3") == 0) { in_firm_average_wage_skill_3 = 1; }
			if(strcmp(buffer, "/firm_average_wage_skill_3") == 0) { in_firm_average_wage_skill_3 = 0; }
			if(strcmp(buffer, "firm_average_wage_skill_4") == 0) { in_firm_average_wage_skill_4 = 1; }
			if(strcmp(buffer, "/firm_average_wage_skill_4") == 0) { in_firm_average_wage_skill_4 = 0; }
			if(strcmp(buffer, "firm_average_wage_skill_5") == 0) { in_firm_average_wage_skill_5 = 1; }
			if(strcmp(buffer, "/firm_average_wage_skill_5") == 0) { in_firm_average_wage_skill_5 = 0; }
			if(strcmp(buffer, "firm_average_g_skill") == 0) { in_firm_average_g_skill = 1; }
			if(strcmp(buffer, "/firm_average_g_skill") == 0) { in_firm_average_g_skill = 0; }
			if(strcmp(buffer, "firm_average_s_skill") == 0) { in_firm_average_s_skill = 1; }
			if(strcmp(buffer, "/firm_average_s_skill") == 0) { in_firm_average_s_skill = 0; }
			if(strcmp(buffer, "firm_average_s_skill_1") == 0) { in_firm_average_s_skill_1 = 1; }
			if(strcmp(buffer, "/firm_average_s_skill_1") == 0) { in_firm_average_s_skill_1 = 0; }
			if(strcmp(buffer, "firm_average_s_skill_2") == 0) { in_firm_average_s_skill_2 = 1; }
			if(strcmp(buffer, "/firm_average_s_skill_2") == 0) { in_firm_average_s_skill_2 = 0; }
			if(strcmp(buffer, "firm_average_s_skill_3") == 0) { in_firm_average_s_skill_3 = 1; }
			if(strcmp(buffer, "/firm_average_s_skill_3") == 0) { in_firm_average_s_skill_3 = 0; }
			if(strcmp(buffer, "firm_average_s_skill_4") == 0) { in_firm_average_s_skill_4 = 1; }
			if(strcmp(buffer, "/firm_average_s_skill_4") == 0) { in_firm_average_s_skill_4 = 0; }
			if(strcmp(buffer, "firm_average_s_skill_5") == 0) { in_firm_average_s_skill_5 = 1; }
			if(strcmp(buffer, "/firm_average_s_skill_5") == 0) { in_firm_average_s_skill_5 = 0; }
			if(strcmp(buffer, "firm_average_quality") == 0) { in_firm_average_quality = 1; }
			if(strcmp(buffer, "/firm_average_quality") == 0) { in_firm_average_quality = 0; }
			if(strcmp(buffer, "firm_average_price") == 0) { in_firm_average_price = 1; }
			if(strcmp(buffer, "/firm_average_price") == 0) { in_firm_average_price = 0; }
			if(strcmp(buffer, "region_firm_data") == 0) { in_region_firm_data = 1; }
			if(strcmp(buffer, "/region_firm_data") == 0) { in_region_firm_data = 0; }
			if(strcmp(buffer, "region_household_data") == 0) { in_region_household_data = 1; }
			if(strcmp(buffer, "/region_household_data") == 0) { in_region_household_data = 0; }
			if(strcmp(buffer, "total_earnings") == 0) { in_total_earnings = 1; }
			if(strcmp(buffer, "/total_earnings") == 0) { in_total_earnings = 0; }
			if(strcmp(buffer, "total_equity") == 0) { in_total_equity = 1; }
			if(strcmp(buffer, "/total_equity") == 0) { in_total_equity = 0; }
			if(strcmp(buffer, "average_debt_earnings_ratio") == 0) { in_average_debt_earnings_ratio = 1; }
			if(strcmp(buffer, "/average_debt_earnings_ratio") == 0) { in_average_debt_earnings_ratio = 0; }
			if(strcmp(buffer, "average_debt_equity_ratio") == 0) { in_average_debt_equity_ratio = 1; }
			if(strcmp(buffer, "/average_debt_equity_ratio") == 0) { in_average_debt_equity_ratio = 0; }
			if(strcmp(buffer, "labour_share_ratio") == 0) { in_labour_share_ratio = 1; }
			if(strcmp(buffer, "/labour_share_ratio") == 0) { in_labour_share_ratio = 0; }
			if(strcmp(buffer, "hpi") == 0) { in_hpi = 1; }
			if(strcmp(buffer, "/hpi") == 0) { in_hpi = 0; }
			if(strcmp(buffer, "hmr_price_data") == 0) { in_hmr_price_data = 1; }
			if(strcmp(buffer, "/hmr_price_data") == 0) { in_hmr_price_data = 0; }
			if(strcmp(buffer, "op_price_data") == 0) { in_op_price_data = 1; }
			if(strcmp(buffer, "/op_price_data") == 0) { in_op_price_data = 0; }
			if(strcmp(buffer, "rent_price_data") == 0) { in_rent_price_data = 1; }
			if(strcmp(buffer, "/rent_price_data") == 0) { in_rent_price_data = 0; }
			if(strcmp(buffer, "hmr_price_mean") == 0) { in_hmr_price_mean = 1; }
			if(strcmp(buffer, "/hmr_price_mean") == 0) { in_hmr_price_mean = 0; }
			if(strcmp(buffer, "op_price_mean") == 0) { in_op_price_mean = 1; }
			if(strcmp(buffer, "/op_price_mean") == 0) { in_op_price_mean = 0; }
			if(strcmp(buffer, "rent_price_mean") == 0) { in_rent_price_mean = 1; }
			if(strcmp(buffer, "/rent_price_mean") == 0) { in_rent_price_mean = 0; }
			if(strcmp(buffer, "count_tenants") == 0) { in_count_tenants = 1; }
			if(strcmp(buffer, "/count_tenants") == 0) { in_count_tenants = 0; }
			if(strcmp(buffer, "count_owners") == 0) { in_count_owners = 1; }
			if(strcmp(buffer, "/count_owners") == 0) { in_count_owners = 0; }
			if(strcmp(buffer, "count_landlords") == 0) { in_count_landlords = 1; }
			if(strcmp(buffer, "/count_landlords") == 0) { in_count_landlords = 0; }
			if(strcmp(buffer, "gdp") == 0) { in_gdp = 1; }
			if(strcmp(buffer, "/gdp") == 0) { in_gdp = 0; }
			if(strcmp(buffer, "monthly_investment_value") == 0) { in_monthly_investment_value = 1; }
			if(strcmp(buffer, "/monthly_investment_value") == 0) { in_monthly_investment_value = 0; }
			if(strcmp(buffer, "monthly_sold_quantity") == 0) { in_monthly_sold_quantity = 1; }
			if(strcmp(buffer, "/monthly_sold_quantity") == 0) { in_monthly_sold_quantity = 0; }
			if(strcmp(buffer, "herfindahl_index") == 0) { in_herfindahl_index = 1; }
			if(strcmp(buffer, "/herfindahl_index") == 0) { in_herfindahl_index = 0; }
			if(strcmp(buffer, "monthly_output") == 0) { in_monthly_output = 1; }
			if(strcmp(buffer, "/monthly_output") == 0) { in_monthly_output = 0; }
			if(strcmp(buffer, "monthly_revenue") == 0) { in_monthly_revenue = 1; }
			if(strcmp(buffer, "/monthly_revenue") == 0) { in_monthly_revenue = 0; }
			if(strcmp(buffer, "monthly_planned_output") == 0) { in_monthly_planned_output = 1; }
			if(strcmp(buffer, "/monthly_planned_output") == 0) { in_monthly_planned_output = 0; }
			if(strcmp(buffer, "history_monthly") == 0) { in_history_monthly = 1; }
			if(strcmp(buffer, "/history_monthly") == 0) { in_history_monthly = 0; }
			if(strcmp(buffer, "history_quarterly") == 0) { in_history_quarterly = 1; }
			if(strcmp(buffer, "/history_quarterly") == 0) { in_history_quarterly = 0; }
			if(strcmp(buffer, "monthly_growth_rates") == 0) { in_monthly_growth_rates = 1; }
			if(strcmp(buffer, "/monthly_growth_rates") == 0) { in_monthly_growth_rates = 0; }
			if(strcmp(buffer, "quarterly_growth_rates") == 0) { in_quarterly_growth_rates = 1; }
			if(strcmp(buffer, "/quarterly_growth_rates") == 0) { in_quarterly_growth_rates = 0; }
			if(strcmp(buffer, "annual_growth_rates_monthly") == 0) { in_annual_growth_rates_monthly = 1; }
			if(strcmp(buffer, "/annual_growth_rates_monthly") == 0) { in_annual_growth_rates_monthly = 0; }
			if(strcmp(buffer, "annual_growth_rates_quarterly") == 0) { in_annual_growth_rates_quarterly = 1; }
			if(strcmp(buffer, "/annual_growth_rates_quarterly") == 0) { in_annual_growth_rates_quarterly = 0; }
			if(strcmp(buffer, "no_firm_births") == 0) { in_no_firm_births = 1; }
			if(strcmp(buffer, "/no_firm_births") == 0) { in_no_firm_births = 0; }
			if(strcmp(buffer, "no_firm_deaths") == 0) { in_no_firm_deaths = 1; }
			if(strcmp(buffer, "/no_firm_deaths") == 0) { in_no_firm_deaths = 0; }
			if(strcmp(buffer, "firm_birth_rate") == 0) { in_firm_birth_rate = 1; }
			if(strcmp(buffer, "/firm_birth_rate") == 0) { in_firm_birth_rate = 0; }
			if(strcmp(buffer, "firm_death_rate") == 0) { in_firm_death_rate = 1; }
			if(strcmp(buffer, "/firm_death_rate") == 0) { in_firm_death_rate = 0; }
			if(strcmp(buffer, "max_firm_creation") == 0) { in_max_firm_creation = 1; }
			if(strcmp(buffer, "/max_firm_creation") == 0) { in_max_firm_creation = 0; }
			if(strcmp(buffer, "recession_started") == 0) { in_recession_started = 1; }
			if(strcmp(buffer, "/recession_started") == 0) { in_recession_started = 0; }
			if(strcmp(buffer, "recession_duration") == 0) { in_recession_duration = 1; }
			if(strcmp(buffer, "/recession_duration") == 0) { in_recession_duration = 0; }
			if(strcmp(buffer, "firm_average_productivity_progress") == 0) { in_firm_average_productivity_progress = 1; }
			if(strcmp(buffer, "/firm_average_productivity_progress") == 0) { in_firm_average_productivity_progress = 0; }
			if(strcmp(buffer, "firm_average_productivity") == 0) { in_firm_average_productivity = 1; }
			if(strcmp(buffer, "/firm_average_productivity") == 0) { in_firm_average_productivity = 0; }
			if(strcmp(buffer, "investment_gdp_ratio") == 0) { in_investment_gdp_ratio = 1; }
			if(strcmp(buffer, "/investment_gdp_ratio") == 0) { in_investment_gdp_ratio = 0; }
			if(strcmp(buffer, "total_capital_stock_units") == 0) { in_total_capital_stock_units = 1; }
			if(strcmp(buffer, "/total_capital_stock_units") == 0) { in_total_capital_stock_units = 0; }
			if(strcmp(buffer, "total_value_mall_inventories") == 0) { in_total_value_mall_inventories = 1; }
			if(strcmp(buffer, "/total_value_mall_inventories") == 0) { in_total_value_mall_inventories = 0; }
			if(strcmp(buffer, "total_dividends") == 0) { in_total_dividends = 1; }
			if(strcmp(buffer, "/total_dividends") == 0) { in_total_dividends = 0; }
			if(strcmp(buffer, "base_wage_offer") == 0) { in_base_wage_offer = 1; }
			if(strcmp(buffer, "/base_wage_offer") == 0) { in_base_wage_offer = 0; }
			if(strcmp(buffer, "job_seperation_rate") == 0) { in_job_seperation_rate = 1; }
			if(strcmp(buffer, "/job_seperation_rate") == 0) { in_job_seperation_rate = 0; }
			if(strcmp(buffer, "job_finding_rate") == 0) { in_job_finding_rate = 1; }
			if(strcmp(buffer, "/job_finding_rate") == 0) { in_job_finding_rate = 0; }
			if(strcmp(buffer, "v_u_ratio") == 0) { in_v_u_ratio = 1; }
			if(strcmp(buffer, "/v_u_ratio") == 0) { in_v_u_ratio = 0; }
			if(strcmp(buffer, "matching_rate") == 0) { in_matching_rate = 1; }
			if(strcmp(buffer, "/matching_rate") == 0) { in_matching_rate = 0; }
			if(strcmp(buffer, "hh_payment_account") == 0) { in_hh_payment_account = 1; }
			if(strcmp(buffer, "/hh_payment_account") == 0) { in_hh_payment_account = 0; }
			if(strcmp(buffer, "plan_sell_house") == 0) { in_plan_sell_house = 1; }
			if(strcmp(buffer, "/plan_sell_house") == 0) { in_plan_sell_house = 0; }
			if(strcmp(buffer, "lookuptable_riskweights_mortgages") == 0) { in_lookuptable_riskweights_mortgages = 1; }
			if(strcmp(buffer, "/lookuptable_riskweights_mortgages") == 0) { in_lookuptable_riskweights_mortgages = 0; }
			if(strcmp(buffer, "basel_risk_weight") == 0) { in_basel_risk_weight = 1; }
			if(strcmp(buffer, "/basel_risk_weight") == 0) { in_basel_risk_weight = 0; }
			if(strcmp(buffer, "firm_npl_daily") == 0) { in_firm_npl_daily = 1; }
			if(strcmp(buffer, "/firm_npl_daily") == 0) { in_firm_npl_daily = 0; }
			if(strcmp(buffer, "firm_ld_daily") == 0) { in_firm_ld_daily = 1; }
			if(strcmp(buffer, "/firm_ld_daily") == 0) { in_firm_ld_daily = 0; }
			if(strcmp(buffer, "firm_ll_daily") == 0) { in_firm_ll_daily = 1; }
			if(strcmp(buffer, "/firm_ll_daily") == 0) { in_firm_ll_daily = 0; }
			if(strcmp(buffer, "firm_pl_daily") == 0) { in_firm_pl_daily = 1; }
			if(strcmp(buffer, "/firm_pl_daily") == 0) { in_firm_pl_daily = 0; }
			if(strcmp(buffer, "firm_pd_qtr") == 0) { in_firm_pd_qtr = 1; }
			if(strcmp(buffer, "/firm_pd_qtr") == 0) { in_firm_pd_qtr = 0; }
			if(strcmp(buffer, "firm_pd_year") == 0) { in_firm_pd_year = 1; }
			if(strcmp(buffer, "/firm_pd_year") == 0) { in_firm_pd_year = 0; }
			if(strcmp(buffer, "firm_lgd_qtr") == 0) { in_firm_lgd_qtr = 1; }
			if(strcmp(buffer, "/firm_lgd_qtr") == 0) { in_firm_lgd_qtr = 0; }
			if(strcmp(buffer, "firm_lgd_year") == 0) { in_firm_lgd_year = 1; }
			if(strcmp(buffer, "/firm_lgd_year") == 0) { in_firm_lgd_year = 0; }
			if(strcmp(buffer, "firm_el_qtr") == 0) { in_firm_el_qtr = 1; }
			if(strcmp(buffer, "/firm_el_qtr") == 0) { in_firm_el_qtr = 0; }
			if(strcmp(buffer, "firm_pd_cycle") == 0) { in_firm_pd_cycle = 1; }
			if(strcmp(buffer, "/firm_pd_cycle") == 0) { in_firm_pd_cycle = 0; }
			if(strcmp(buffer, "firm_lgd_cycle") == 0) { in_firm_lgd_cycle = 1; }
			if(strcmp(buffer, "/firm_lgd_cycle") == 0) { in_firm_lgd_cycle = 0; }
			if(strcmp(buffer, "firm_pd_ttc") == 0) { in_firm_pd_ttc = 1; }
			if(strcmp(buffer, "/firm_pd_ttc") == 0) { in_firm_pd_ttc = 0; }
			if(strcmp(buffer, "firm_lgd_ttc") == 0) { in_firm_lgd_ttc = 1; }
			if(strcmp(buffer, "/firm_lgd_ttc") == 0) { in_firm_lgd_ttc = 0; }
			if(strcmp(buffer, "hh_npl_daily") == 0) { in_hh_npl_daily = 1; }
			if(strcmp(buffer, "/hh_npl_daily") == 0) { in_hh_npl_daily = 0; }
			if(strcmp(buffer, "hh_ll_daily") == 0) { in_hh_ll_daily = 1; }
			if(strcmp(buffer, "/hh_ll_daily") == 0) { in_hh_ll_daily = 0; }
			if(strcmp(buffer, "hh_ld_daily") == 0) { in_hh_ld_daily = 1; }
			if(strcmp(buffer, "/hh_ld_daily") == 0) { in_hh_ld_daily = 0; }
			if(strcmp(buffer, "hh_pl_daily") == 0) { in_hh_pl_daily = 1; }
			if(strcmp(buffer, "/hh_pl_daily") == 0) { in_hh_pl_daily = 0; }
			if(strcmp(buffer, "hh_pd_qtr") == 0) { in_hh_pd_qtr = 1; }
			if(strcmp(buffer, "/hh_pd_qtr") == 0) { in_hh_pd_qtr = 0; }
			if(strcmp(buffer, "hh_pd_year") == 0) { in_hh_pd_year = 1; }
			if(strcmp(buffer, "/hh_pd_year") == 0) { in_hh_pd_year = 0; }
			if(strcmp(buffer, "hh_lgd_qtr") == 0) { in_hh_lgd_qtr = 1; }
			if(strcmp(buffer, "/hh_lgd_qtr") == 0) { in_hh_lgd_qtr = 0; }
			if(strcmp(buffer, "hh_lgd_year") == 0) { in_hh_lgd_year = 1; }
			if(strcmp(buffer, "/hh_lgd_year") == 0) { in_hh_lgd_year = 0; }
			if(strcmp(buffer, "hh_el_qtr") == 0) { in_hh_el_qtr = 1; }
			if(strcmp(buffer, "/hh_el_qtr") == 0) { in_hh_el_qtr = 0; }
			if(strcmp(buffer, "hh_pd_cycle") == 0) { in_hh_pd_cycle = 1; }
			if(strcmp(buffer, "/hh_pd_cycle") == 0) { in_hh_pd_cycle = 0; }
			if(strcmp(buffer, "hh_lgd_cycle") == 0) { in_hh_lgd_cycle = 1; }
			if(strcmp(buffer, "/hh_lgd_cycle") == 0) { in_hh_lgd_cycle = 0; }
			if(strcmp(buffer, "hh_pd_ttc") == 0) { in_hh_pd_ttc = 1; }
			if(strcmp(buffer, "/hh_pd_ttc") == 0) { in_hh_pd_ttc = 0; }
			if(strcmp(buffer, "hh_lgd_ttc") == 0) { in_hh_lgd_ttc = 1; }
			if(strcmp(buffer, "/hh_lgd_ttc") == 0) { in_hh_lgd_ttc = 0; }
			if(strcmp(buffer, "cash") == 0) { in_cash = 1; }
			if(strcmp(buffer, "/cash") == 0) { in_cash = 0; }
			if(strcmp(buffer, "reserves") == 0) { in_reserves = 1; }
			if(strcmp(buffer, "/reserves") == 0) { in_reserves = 0; }
			if(strcmp(buffer, "regulatory_reserves") == 0) { in_regulatory_reserves = 1; }
			if(strcmp(buffer, "/regulatory_reserves") == 0) { in_regulatory_reserves = 0; }
			if(strcmp(buffer, "total_credit") == 0) { in_total_credit = 1; }
			if(strcmp(buffer, "/total_credit") == 0) { in_total_credit = 0; }
			if(strcmp(buffer, "ecb_debt") == 0) { in_ecb_debt = 1; }
			if(strcmp(buffer, "/ecb_debt") == 0) { in_ecb_debt = 0; }
			if(strcmp(buffer, "risk_exposure") == 0) { in_risk_exposure = 1; }
			if(strcmp(buffer, "/risk_exposure") == 0) { in_risk_exposure = 0; }
			if(strcmp(buffer, "deposit_interest_rate") == 0) { in_deposit_interest_rate = 1; }
			if(strcmp(buffer, "/deposit_interest_rate") == 0) { in_deposit_interest_rate = 0; }
			if(strcmp(buffer, "bank_gamma") == 0) { in_bank_gamma = 1; }
			if(strcmp(buffer, "/bank_gamma") == 0) { in_bank_gamma = 0; }
			if(strcmp(buffer, "profits") == 0) { in_profits = 1; }
			if(strcmp(buffer, "/profits") == 0) { in_profits = 0; }
			if(strcmp(buffer, "bank_dividend_rate") == 0) { in_bank_dividend_rate = 1; }
			if(strcmp(buffer, "/bank_dividend_rate") == 0) { in_bank_dividend_rate = 0; }
			if(strcmp(buffer, "debt_period") == 0) { in_debt_period = 1; }
			if(strcmp(buffer, "/debt_period") == 0) { in_debt_period = 0; }
			if(strcmp(buffer, "loan_request_message_found") == 0) { in_loan_request_message_found = 1; }
			if(strcmp(buffer, "/loan_request_message_found") == 0) { in_loan_request_message_found = 0; }
			if(strcmp(buffer, "deposits") == 0) { in_deposits = 1; }
			if(strcmp(buffer, "/deposits") == 0) { in_deposits = 0; }
			if(strcmp(buffer, "deposits_previous") == 0) { in_deposits_previous = 1; }
			if(strcmp(buffer, "/deposits_previous") == 0) { in_deposits_previous = 0; }
			if(strcmp(buffer, "firm_loan_installments") == 0) { in_firm_loan_installments = 1; }
			if(strcmp(buffer, "/firm_loan_installments") == 0) { in_firm_loan_installments = 0; }
			if(strcmp(buffer, "firm_loan_installments_in_calendar_month") == 0) { in_firm_loan_installments_in_calendar_month = 1; }
			if(strcmp(buffer, "/firm_loan_installments_in_calendar_month") == 0) { in_firm_loan_installments_in_calendar_month = 0; }
			if(strcmp(buffer, "firm_interest_payments") == 0) { in_firm_interest_payments = 1; }
			if(strcmp(buffer, "/firm_interest_payments") == 0) { in_firm_interest_payments = 0; }
			if(strcmp(buffer, "firm_interest_payments_in_calendar_month") == 0) { in_firm_interest_payments_in_calendar_month = 1; }
			if(strcmp(buffer, "/firm_interest_payments_in_calendar_month") == 0) { in_firm_interest_payments_in_calendar_month = 0; }
			if(strcmp(buffer, "firm_loan_issues") == 0) { in_firm_loan_issues = 1; }
			if(strcmp(buffer, "/firm_loan_issues") == 0) { in_firm_loan_issues = 0; }
			if(strcmp(buffer, "ecb_interest_payment") == 0) { in_ecb_interest_payment = 1; }
			if(strcmp(buffer, "/ecb_interest_payment") == 0) { in_ecb_interest_payment = 0; }
			if(strcmp(buffer, "total_dividends_in_calendar_month") == 0) { in_total_dividends_in_calendar_month = 1; }
			if(strcmp(buffer, "/total_dividends_in_calendar_month") == 0) { in_total_dividends_in_calendar_month = 0; }
			if(strcmp(buffer, "taxes") == 0) { in_taxes = 1; }
			if(strcmp(buffer, "/taxes") == 0) { in_taxes = 0; }
			if(strcmp(buffer, "dividend_per_share") == 0) { in_dividend_per_share = 1; }
			if(strcmp(buffer, "/dividend_per_share") == 0) { in_dividend_per_share = 0; }
			if(strcmp(buffer, "leverage_ratio") == 0) { in_leverage_ratio = 1; }
			if(strcmp(buffer, "/leverage_ratio") == 0) { in_leverage_ratio = 0; }
			if(strcmp(buffer, "reserve_deposit_ratio") == 0) { in_reserve_deposit_ratio = 1; }
			if(strcmp(buffer, "/reserve_deposit_ratio") == 0) { in_reserve_deposit_ratio = 0; }
			if(strcmp(buffer, "mean_interest_rate") == 0) { in_mean_interest_rate = 1; }
			if(strcmp(buffer, "/mean_interest_rate") == 0) { in_mean_interest_rate = 0; }
			if(strcmp(buffer, "sum_new_interest_rates_in_calendar_month") == 0) { in_sum_new_interest_rates_in_calendar_month = 1; }
			if(strcmp(buffer, "/sum_new_interest_rates_in_calendar_month") == 0) { in_sum_new_interest_rates_in_calendar_month = 0; }
			if(strcmp(buffer, "no_new_loans_in_calendar_month") == 0) { in_no_new_loans_in_calendar_month = 1; }
			if(strcmp(buffer, "/no_new_loans_in_calendar_month") == 0) { in_no_new_loans_in_calendar_month = 0; }
			if(strcmp(buffer, "paid_interest_daily") == 0) { in_paid_interest_daily = 1; }
			if(strcmp(buffer, "/paid_interest_daily") == 0) { in_paid_interest_daily = 0; }
			if(strcmp(buffer, "paid_interest_in_calendar_month") == 0) { in_paid_interest_in_calendar_month = 1; }
			if(strcmp(buffer, "/paid_interest_in_calendar_month") == 0) { in_paid_interest_in_calendar_month = 0; }
			if(strcmp(buffer, "excess_risk_exposure") == 0) { in_excess_risk_exposure = 1; }
			if(strcmp(buffer, "/excess_risk_exposure") == 0) { in_excess_risk_exposure = 0; }
			if(strcmp(buffer, "excess_liquidity") == 0) { in_excess_liquidity = 1; }
			if(strcmp(buffer, "/excess_liquidity") == 0) { in_excess_liquidity = 0; }
			if(strcmp(buffer, "total_bad_debt_calendar_month") == 0) { in_total_bad_debt_calendar_month = 1; }
			if(strcmp(buffer, "/total_bad_debt_calendar_month") == 0) { in_total_bad_debt_calendar_month = 0; }
			if(strcmp(buffer, "proba_default_distribution") == 0) { in_proba_default_distribution = 1; }
			if(strcmp(buffer, "/proba_default_distribution") == 0) { in_proba_default_distribution = 0; }
			if(strcmp(buffer, "liquidity_coverage_ratio") == 0) { in_liquidity_coverage_ratio = 1; }
			if(strcmp(buffer, "/liquidity_coverage_ratio") == 0) { in_liquidity_coverage_ratio = 0; }
			if(strcmp(buffer, "bank_balance_sheet_calendar") == 0) { in_bank_balance_sheet_calendar = 1; }
			if(strcmp(buffer, "/bank_balance_sheet_calendar") == 0) { in_bank_balance_sheet_calendar = 0; }
			if(strcmp(buffer, "bank_stocks_calendar") == 0) { in_bank_stocks_calendar = 1; }
			if(strcmp(buffer, "/bank_stocks_calendar") == 0) { in_bank_stocks_calendar = 0; }
			if(strcmp(buffer, "bank_outflows_calendar") == 0) { in_bank_outflows_calendar = 1; }
			if(strcmp(buffer, "/bank_outflows_calendar") == 0) { in_bank_outflows_calendar = 0; }
			if(strcmp(buffer, "bank_inflows_calendar") == 0) { in_bank_inflows_calendar = 1; }
			if(strcmp(buffer, "/bank_inflows_calendar") == 0) { in_bank_inflows_calendar = 0; }
			if(strcmp(buffer, "loan_loss_reserve_firm_loans") == 0) { in_loan_loss_reserve_firm_loans = 1; }
			if(strcmp(buffer, "/loan_loss_reserve_firm_loans") == 0) { in_loan_loss_reserve_firm_loans = 0; }
			if(strcmp(buffer, "loan_loss_reserve_mortgage_loans") == 0) { in_loan_loss_reserve_mortgage_loans = 1; }
			if(strcmp(buffer, "/loan_loss_reserve_mortgage_loans") == 0) { in_loan_loss_reserve_mortgage_loans = 0; }
			if(strcmp(buffer, "mortgage_portfolio") == 0) { in_mortgage_portfolio = 1; }
			if(strcmp(buffer, "/mortgage_portfolio") == 0) { in_mortgage_portfolio = 0; }
			if(strcmp(buffer, "bank_inflows_monthly_mortgage_payments") == 0) { in_bank_inflows_monthly_mortgage_payments = 1; }
			if(strcmp(buffer, "/bank_inflows_monthly_mortgage_payments") == 0) { in_bank_inflows_monthly_mortgage_payments = 0; }
			if(strcmp(buffer, "bank_outflows_monthly_mortgage_issues") == 0) { in_bank_outflows_monthly_mortgage_issues = 1; }
			if(strcmp(buffer, "/bank_outflows_monthly_mortgage_issues") == 0) { in_bank_outflows_monthly_mortgage_issues = 0; }
			if(strcmp(buffer, "no_monthly_new_mortgages_flow") == 0) { in_no_monthly_new_mortgages_flow = 1; }
			if(strcmp(buffer, "/no_monthly_new_mortgages_flow") == 0) { in_no_monthly_new_mortgages_flow = 0; }
			if(strcmp(buffer, "no_mortgages_outstanding") == 0) { in_no_mortgages_outstanding = 1; }
			if(strcmp(buffer, "/no_mortgages_outstanding") == 0) { in_no_mortgages_outstanding = 0; }
			if(strcmp(buffer, "seized_collateral") == 0) { in_seized_collateral = 1; }
			if(strcmp(buffer, "/seized_collateral") == 0) { in_seized_collateral = 0; }
			if(strcmp(buffer, "list_of_regions") == 0) { in_list_of_regions = 1; }
			if(strcmp(buffer, "/list_of_regions") == 0) { in_list_of_regions = 0; }
			if(strcmp(buffer, "gdp_fraction_consumption") == 0) { in_gdp_fraction_consumption = 1; }
			if(strcmp(buffer, "/gdp_fraction_consumption") == 0) { in_gdp_fraction_consumption = 0; }
			if(strcmp(buffer, "gdp_fraction_investment") == 0) { in_gdp_fraction_investment = 1; }
			if(strcmp(buffer, "/gdp_fraction_investment") == 0) { in_gdp_fraction_investment = 0; }
			if(strcmp(buffer, "monthly_tax_revenues") == 0) { in_monthly_tax_revenues = 1; }
			if(strcmp(buffer, "/monthly_tax_revenues") == 0) { in_monthly_tax_revenues = 0; }
			if(strcmp(buffer, "yearly_tax_revenues") == 0) { in_yearly_tax_revenues = 1; }
			if(strcmp(buffer, "/yearly_tax_revenues") == 0) { in_yearly_tax_revenues = 0; }
			if(strcmp(buffer, "monthly_benefit_payment") == 0) { in_monthly_benefit_payment = 1; }
			if(strcmp(buffer, "/monthly_benefit_payment") == 0) { in_monthly_benefit_payment = 0; }
			if(strcmp(buffer, "yearly_benefit_payment") == 0) { in_yearly_benefit_payment = 1; }
			if(strcmp(buffer, "/yearly_benefit_payment") == 0) { in_yearly_benefit_payment = 0; }
			if(strcmp(buffer, "hh_transfer_payment") == 0) { in_hh_transfer_payment = 1; }
			if(strcmp(buffer, "/hh_transfer_payment") == 0) { in_hh_transfer_payment = 0; }
			if(strcmp(buffer, "firm_transfer_payment") == 0) { in_firm_transfer_payment = 1; }
			if(strcmp(buffer, "/firm_transfer_payment") == 0) { in_firm_transfer_payment = 0; }
			if(strcmp(buffer, "monthly_transfer_payment") == 0) { in_monthly_transfer_payment = 1; }
			if(strcmp(buffer, "/monthly_transfer_payment") == 0) { in_monthly_transfer_payment = 0; }
			if(strcmp(buffer, "yearly_transfer_payment") == 0) { in_yearly_transfer_payment = 1; }
			if(strcmp(buffer, "/yearly_transfer_payment") == 0) { in_yearly_transfer_payment = 0; }
			if(strcmp(buffer, "hh_subsidy_pct") == 0) { in_hh_subsidy_pct = 1; }
			if(strcmp(buffer, "/hh_subsidy_pct") == 0) { in_hh_subsidy_pct = 0; }
			if(strcmp(buffer, "firm_subsidy_pct") == 0) { in_firm_subsidy_pct = 1; }
			if(strcmp(buffer, "/firm_subsidy_pct") == 0) { in_firm_subsidy_pct = 0; }
			if(strcmp(buffer, "regional_firm_subsidy") == 0) { in_regional_firm_subsidy = 1; }
			if(strcmp(buffer, "/regional_firm_subsidy") == 0) { in_regional_firm_subsidy = 0; }
			if(strcmp(buffer, "subsidy_flag") == 0) { in_subsidy_flag = 1; }
			if(strcmp(buffer, "/subsidy_flag") == 0) { in_subsidy_flag = 0; }
			if(strcmp(buffer, "gov_interest_rate") == 0) { in_gov_interest_rate = 1; }
			if(strcmp(buffer, "/gov_interest_rate") == 0) { in_gov_interest_rate = 0; }
			if(strcmp(buffer, "monthly_bond_interest_payment") == 0) { in_monthly_bond_interest_payment = 1; }
			if(strcmp(buffer, "/monthly_bond_interest_payment") == 0) { in_monthly_bond_interest_payment = 0; }
			if(strcmp(buffer, "monthly_subsidy_payment") == 0) { in_monthly_subsidy_payment = 1; }
			if(strcmp(buffer, "/monthly_subsidy_payment") == 0) { in_monthly_subsidy_payment = 0; }
			if(strcmp(buffer, "monthly_investment_expenditure") == 0) { in_monthly_investment_expenditure = 1; }
			if(strcmp(buffer, "/monthly_investment_expenditure") == 0) { in_monthly_investment_expenditure = 0; }
			if(strcmp(buffer, "monthly_budget_balance") == 0) { in_monthly_budget_balance = 1; }
			if(strcmp(buffer, "/monthly_budget_balance") == 0) { in_monthly_budget_balance = 0; }
			if(strcmp(buffer, "monthly_gdp") == 0) { in_monthly_gdp = 1; }
			if(strcmp(buffer, "/monthly_gdp") == 0) { in_monthly_gdp = 0; }
			if(strcmp(buffer, "monthly_budget_balance_gdp_fraction") == 0) { in_monthly_budget_balance_gdp_fraction = 1; }
			if(strcmp(buffer, "/monthly_budget_balance_gdp_fraction") == 0) { in_monthly_budget_balance_gdp_fraction = 0; }
			if(strcmp(buffer, "monthly_consumption_budget") == 0) { in_monthly_consumption_budget = 1; }
			if(strcmp(buffer, "/monthly_consumption_budget") == 0) { in_monthly_consumption_budget = 0; }
			if(strcmp(buffer, "monthly_investment_budget") == 0) { in_monthly_investment_budget = 1; }
			if(strcmp(buffer, "/monthly_investment_budget") == 0) { in_monthly_investment_budget = 0; }
			if(strcmp(buffer, "monthly_income") == 0) { in_monthly_income = 1; }
			if(strcmp(buffer, "/monthly_income") == 0) { in_monthly_income = 0; }
			if(strcmp(buffer, "monthly_expenditure") == 0) { in_monthly_expenditure = 1; }
			if(strcmp(buffer, "/monthly_expenditure") == 0) { in_monthly_expenditure = 0; }
			if(strcmp(buffer, "yearly_subsidy_payment") == 0) { in_yearly_subsidy_payment = 1; }
			if(strcmp(buffer, "/yearly_subsidy_payment") == 0) { in_yearly_subsidy_payment = 0; }
			if(strcmp(buffer, "yearly_bond_interest_payment") == 0) { in_yearly_bond_interest_payment = 1; }
			if(strcmp(buffer, "/yearly_bond_interest_payment") == 0) { in_yearly_bond_interest_payment = 0; }
			if(strcmp(buffer, "yearly_investment_expenditure") == 0) { in_yearly_investment_expenditure = 1; }
			if(strcmp(buffer, "/yearly_investment_expenditure") == 0) { in_yearly_investment_expenditure = 0; }
			if(strcmp(buffer, "yearly_consumption_expenditure") == 0) { in_yearly_consumption_expenditure = 1; }
			if(strcmp(buffer, "/yearly_consumption_expenditure") == 0) { in_yearly_consumption_expenditure = 0; }
			if(strcmp(buffer, "yearly_income") == 0) { in_yearly_income = 1; }
			if(strcmp(buffer, "/yearly_income") == 0) { in_yearly_income = 0; }
			if(strcmp(buffer, "yearly_expenditure") == 0) { in_yearly_expenditure = 1; }
			if(strcmp(buffer, "/yearly_expenditure") == 0) { in_yearly_expenditure = 0; }
			if(strcmp(buffer, "yearly_budget_balance") == 0) { in_yearly_budget_balance = 1; }
			if(strcmp(buffer, "/yearly_budget_balance") == 0) { in_yearly_budget_balance = 0; }
			if(strcmp(buffer, "total_money_financing") == 0) { in_total_money_financing = 1; }
			if(strcmp(buffer, "/total_money_financing") == 0) { in_total_money_financing = 0; }
			if(strcmp(buffer, "total_bond_financing") == 0) { in_total_bond_financing = 1; }
			if(strcmp(buffer, "/total_bond_financing") == 0) { in_total_bond_financing = 0; }
			if(strcmp(buffer, "country_wide_mean_wage") == 0) { in_country_wide_mean_wage = 1; }
			if(strcmp(buffer, "/country_wide_mean_wage") == 0) { in_country_wide_mean_wage = 0; }
			if(strcmp(buffer, "num_unemployed") == 0) { in_num_unemployed = 1; }
			if(strcmp(buffer, "/num_unemployed") == 0) { in_num_unemployed = 0; }
			if(strcmp(buffer, "yearly_gdp") == 0) { in_yearly_gdp = 1; }
			if(strcmp(buffer, "/yearly_gdp") == 0) { in_yearly_gdp = 0; }
			if(strcmp(buffer, "previous_year_gdp") == 0) { in_previous_year_gdp = 1; }
			if(strcmp(buffer, "/previous_year_gdp") == 0) { in_previous_year_gdp = 0; }
			if(strcmp(buffer, "gdp_growth") == 0) { in_gdp_growth = 1; }
			if(strcmp(buffer, "/gdp_growth") == 0) { in_gdp_growth = 0; }
			if(strcmp(buffer, "gdp_forecast") == 0) { in_gdp_forecast = 1; }
			if(strcmp(buffer, "/gdp_forecast") == 0) { in_gdp_forecast = 0; }
			if(strcmp(buffer, "yearly_income_forecast") == 0) { in_yearly_income_forecast = 1; }
			if(strcmp(buffer, "/yearly_income_forecast") == 0) { in_yearly_income_forecast = 0; }
			if(strcmp(buffer, "yearly_expenditure_budget") == 0) { in_yearly_expenditure_budget = 1; }
			if(strcmp(buffer, "/yearly_expenditure_budget") == 0) { in_yearly_expenditure_budget = 0; }
			if(strcmp(buffer, "budget_balance_forecast") == 0) { in_budget_balance_forecast = 1; }
			if(strcmp(buffer, "/budget_balance_forecast") == 0) { in_budget_balance_forecast = 0; }
			if(strcmp(buffer, "yearly_consumption_budget") == 0) { in_yearly_consumption_budget = 1; }
			if(strcmp(buffer, "/yearly_consumption_budget") == 0) { in_yearly_consumption_budget = 0; }
			if(strcmp(buffer, "yearly_investment_budget") == 0) { in_yearly_investment_budget = 1; }
			if(strcmp(buffer, "/yearly_investment_budget") == 0) { in_yearly_investment_budget = 0; }
			if(strcmp(buffer, "yearly_budget_balance_gdp_fraction") == 0) { in_yearly_budget_balance_gdp_fraction = 1; }
			if(strcmp(buffer, "/yearly_budget_balance_gdp_fraction") == 0) { in_yearly_budget_balance_gdp_fraction = 0; }
			if(strcmp(buffer, "cumulated_deficit") == 0) { in_cumulated_deficit = 1; }
			if(strcmp(buffer, "/cumulated_deficit") == 0) { in_cumulated_deficit = 0; }
			if(strcmp(buffer, "inflation_rate") == 0) { in_inflation_rate = 1; }
			if(strcmp(buffer, "/inflation_rate") == 0) { in_inflation_rate = 0; }
			if(strcmp(buffer, "human_capital_policy_installation_date_in_years") == 0) { in_human_capital_policy_installation_date_in_years = 1; }
			if(strcmp(buffer, "/human_capital_policy_installation_date_in_years") == 0) { in_human_capital_policy_installation_date_in_years = 0; }
			if(strcmp(buffer, "new_skill_distribution") == 0) { in_new_skill_distribution = 1; }
			if(strcmp(buffer, "/new_skill_distribution") == 0) { in_new_skill_distribution = 0; }
			if(strcmp(buffer, "gov_balance_sheet_calendar") == 0) { in_gov_balance_sheet_calendar = 1; }
			if(strcmp(buffer, "/gov_balance_sheet_calendar") == 0) { in_gov_balance_sheet_calendar = 0; }
			if(strcmp(buffer, "gov_stocks_calendar") == 0) { in_gov_stocks_calendar = 1; }
			if(strcmp(buffer, "/gov_stocks_calendar") == 0) { in_gov_stocks_calendar = 0; }
			if(strcmp(buffer, "gov_outflows_calendar") == 0) { in_gov_outflows_calendar = 1; }
			if(strcmp(buffer, "/gov_outflows_calendar") == 0) { in_gov_outflows_calendar = 0; }
			if(strcmp(buffer, "gov_inflows_calendar") == 0) { in_gov_inflows_calendar = 1; }
			if(strcmp(buffer, "/gov_inflows_calendar") == 0) { in_gov_inflows_calendar = 0; }
			if(strcmp(buffer, "fiat_money") == 0) { in_fiat_money = 1; }
			if(strcmp(buffer, "/fiat_money") == 0) { in_fiat_money = 0; }
			if(strcmp(buffer, "fiat_money_banks") == 0) { in_fiat_money_banks = 1; }
			if(strcmp(buffer, "/fiat_money_banks") == 0) { in_fiat_money_banks = 0; }
			if(strcmp(buffer, "fiat_money_firms") == 0) { in_fiat_money_firms = 1; }
			if(strcmp(buffer, "/fiat_money_firms") == 0) { in_fiat_money_firms = 0; }
			if(strcmp(buffer, "ecb_deposits") == 0) { in_ecb_deposits = 1; }
			if(strcmp(buffer, "/ecb_deposits") == 0) { in_ecb_deposits = 0; }
			if(strcmp(buffer, "accounts_banks") == 0) { in_accounts_banks = 1; }
			if(strcmp(buffer, "/accounts_banks") == 0) { in_accounts_banks = 0; }
			if(strcmp(buffer, "accounts_govs") == 0) { in_accounts_govs = 1; }
			if(strcmp(buffer, "/accounts_govs") == 0) { in_accounts_govs = 0; }
			if(strcmp(buffer, "ecb_balance_sheet_calendar") == 0) { in_ecb_balance_sheet_calendar = 1; }
			if(strcmp(buffer, "/ecb_balance_sheet_calendar") == 0) { in_ecb_balance_sheet_calendar = 0; }
			if(strcmp(buffer, "ecb_stocks_calendar") == 0) { in_ecb_stocks_calendar = 1; }
			if(strcmp(buffer, "/ecb_stocks_calendar") == 0) { in_ecb_stocks_calendar = 0; }
			if(strcmp(buffer, "ecb_outflows_calendar") == 0) { in_ecb_outflows_calendar = 1; }
			if(strcmp(buffer, "/ecb_outflows_calendar") == 0) { in_ecb_outflows_calendar = 0; }
			if(strcmp(buffer, "ecb_inflows_calendar") == 0) { in_ecb_inflows_calendar = 1; }
			if(strcmp(buffer, "/ecb_inflows_calendar") == 0) { in_ecb_inflows_calendar = 0; }
			if(strcmp(buffer, "bond_holdings_value") == 0) { in_bond_holdings_value = 1; }
			if(strcmp(buffer, "/bond_holdings_value") == 0) { in_bond_holdings_value = 0; }
			if(strcmp(buffer, "nr_gov_bonds") == 0) { in_nr_gov_bonds = 1; }
			if(strcmp(buffer, "/nr_gov_bonds") == 0) { in_nr_gov_bonds = 0; }
			if(strcmp(buffer, "fiat_money_govs") == 0) { in_fiat_money_govs = 1; }
			if(strcmp(buffer, "/fiat_money_govs") == 0) { in_fiat_money_govs = 0; }
			if(strcmp(buffer, "fiat_money_bond_govs") == 0) { in_fiat_money_bond_govs = 1; }
			if(strcmp(buffer, "/fiat_money_bond_govs") == 0) { in_fiat_money_bond_govs = 0; }
			if(strcmp(buffer, "bank_interest") == 0) { in_bank_interest = 1; }
			if(strcmp(buffer, "/bank_interest") == 0) { in_bank_interest = 0; }
			if(strcmp(buffer, "gov_interest") == 0) { in_gov_interest = 1; }
			if(strcmp(buffer, "/gov_interest") == 0) { in_gov_interest = 0; }
			if(strcmp(buffer, "gov_bond_purchase") == 0) { in_gov_bond_purchase = 1; }
			if(strcmp(buffer, "/gov_bond_purchase") == 0) { in_gov_bond_purchase = 0; }
			if(strcmp(buffer, "pending_orders") == 0) { in_pending_orders = 1; }
			if(strcmp(buffer, "/pending_orders") == 0) { in_pending_orders = 0; }
			if(strcmp(buffer, "processed_orders") == 0) { in_processed_orders = 1; }
			if(strcmp(buffer, "/processed_orders") == 0) { in_processed_orders = 0; }
			if(strcmp(buffer, "stock_index") == 0) { in_stock_index = 1; }
			if(strcmp(buffer, "/stock_index") == 0) { in_stock_index = 0; }
			if(strcmp(buffer, "dsratio") == 0) { in_dsratio = 1; }
			if(strcmp(buffer, "/dsratio") == 0) { in_dsratio = 0; }
			if(strcmp(buffer, "random_numbers_normal") == 0) { in_random_numbers_normal = 1; }
			if(strcmp(buffer, "/random_numbers_normal") == 0) { in_random_numbers_normal = 0; }
			if(strcmp(buffer, "monthly_counter_total_dividend") == 0) { in_monthly_counter_total_dividend = 1; }
			if(strcmp(buffer, "/monthly_counter_total_dividend") == 0) { in_monthly_counter_total_dividend = 0; }
			if(strcmp(buffer, "stock_index_price") == 0) { in_stock_index_price = 1; }
			if(strcmp(buffer, "/stock_index_price") == 0) { in_stock_index_price = 0; }
			if(strcmp(buffer, "house_auction") == 0) { in_house_auction = 1; }
			if(strcmp(buffer, "/house_auction") == 0) { in_house_auction = 0; }
			if(strcmp(buffer, "rental_auction") == 0) { in_rental_auction = 1; }
			if(strcmp(buffer, "/rental_auction") == 0) { in_rental_auction = 0; }
			if(strcmp(buffer, "init_tenants") == 0) { in_init_tenants = 1; }
			if(strcmp(buffer, "/init_tenants") == 0) { in_init_tenants = 0; }
			if(strcmp(buffer, "init_landlords") == 0) { in_init_landlords = 1; }
			if(strcmp(buffer, "/init_landlords") == 0) { in_init_landlords = 0; }
			if(strcmp(buffer, "init_owners") == 0) { in_init_owners = 1; }
			if(strcmp(buffer, "/init_owners") == 0) { in_init_owners = 0; }
			if(strcmp(buffer, "network_banks") == 0) { in_network_banks = 1; }
			if(strcmp(buffer, "/network_banks") == 0) { in_network_banks = 0; }
			if(strcmp(buffer, "network_firms") == 0) { in_network_firms = 1; }
			if(strcmp(buffer, "/network_firms") == 0) { in_network_firms = 0; }
			if(strcmp(buffer, "network_hhs") == 0) { in_network_hhs = 1; }
			if(strcmp(buffer, "/network_hhs") == 0) { in_network_hhs = 0; }
			if(strcmp(buffer, "network") == 0) { in_network = 1; }
			if(strcmp(buffer, "/network") == 0) { in_network = 0; }
			if(strcmp(buffer, "total_no_loans_banks") == 0) { in_total_no_loans_banks = 1; }
			if(strcmp(buffer, "/total_no_loans_banks") == 0) { in_total_no_loans_banks = 0; }
			if(strcmp(buffer, "total_no_loans_firms") == 0) { in_total_no_loans_firms = 1; }
			if(strcmp(buffer, "/total_no_loans_firms") == 0) { in_total_no_loans_firms = 0; }
			if(strcmp(buffer, "total_no_loans_hh") == 0) { in_total_no_loans_hh = 1; }
			if(strcmp(buffer, "/total_no_loans_hh") == 0) { in_total_no_loans_hh = 0; }
			if(strcmp(buffer, "total_value_loans_banks") == 0) { in_total_value_loans_banks = 1; }
			if(strcmp(buffer, "/total_value_loans_banks") == 0) { in_total_value_loans_banks = 0; }
			if(strcmp(buffer, "total_value_loans_firms") == 0) { in_total_value_loans_firms = 1; }
			if(strcmp(buffer, "/total_value_loans_firms") == 0) { in_total_value_loans_firms = 0; }
			if(strcmp(buffer, "total_value_loans_hh") == 0) { in_total_value_loans_hh = 1; }
			if(strcmp(buffer, "/total_value_loans_hh") == 0) { in_total_value_loans_hh = 0; }
			if(strcmp(buffer, "firm_loan_no_dist") == 0) { in_firm_loan_no_dist = 1; }
			if(strcmp(buffer, "/firm_loan_no_dist") == 0) { in_firm_loan_no_dist = 0; }
			if(strcmp(buffer, "firm_loan_value_dist") == 0) { in_firm_loan_value_dist = 1; }
			if(strcmp(buffer, "/firm_loan_value_dist") == 0) { in_firm_loan_value_dist = 0; }
			if(strcmp(buffer, "clustering_coefficient") == 0) { in_clustering_coefficient = 1; }
			if(strcmp(buffer, "/clustering_coefficient") == 0) { in_clustering_coefficient = 0; }
			if(strcmp(buffer, "homophily_index") == 0) { in_homophily_index = 1; }
			if(strcmp(buffer, "/homophily_index") == 0) { in_homophily_index = 0; }
			if(strcmp(buffer, "average_path_length") == 0) { in_average_path_length = 1; }
			if(strcmp(buffer, "/average_path_length") == 0) { in_average_path_length = 0; }
			if(strcmp(buffer, "links") == 0) { in_links = 1; }
			if(strcmp(buffer, "/links") == 0) { in_links = 0; }
			
			index = 0;
			buffer[index] = '\0';
		}
		else if(c == '<')
		{
			buffer[index] = '\0';
			
			if(in_itno && FLAME_in_xagent == 0) *itno = atoi(buffer);
			if(FLAME_in_xagent == 1)
			{
				if(FLAME_in_name == 1)
				{
					strcpy(agentname, buffer);

					if(strcmp(agentname, "Firm") == 0)
					{
						current_Firm_agent = init_Firm_agent();
						in_Firm_agent = 1;
					}
					else if(strcmp(agentname, "Household") == 0)
					{
						current_Household_agent = init_Household_agent();
						in_Household_agent = 1;
					}
					else if(strcmp(agentname, "Mall") == 0)
					{
						current_Mall_agent = init_Mall_agent();
						in_Mall_agent = 1;
					}
					else if(strcmp(agentname, "IGFirm") == 0)
					{
						current_IGFirm_agent = init_IGFirm_agent();
						in_IGFirm_agent = 1;
					}
					else if(strcmp(agentname, "Eurostat") == 0)
					{
						current_Eurostat_agent = init_Eurostat_agent();
						in_Eurostat_agent = 1;
					}
					else if(strcmp(agentname, "Bank") == 0)
					{
						current_Bank_agent = init_Bank_agent();
						in_Bank_agent = 1;
					}
					else if(strcmp(agentname, "Government") == 0)
					{
						current_Government_agent = init_Government_agent();
						in_Government_agent = 1;
					}
					else if(strcmp(agentname, "CentralBank") == 0)
					{
						current_CentralBank_agent = init_CentralBank_agent();
						in_CentralBank_agent = 1;
					}
					else if(strcmp(agentname, "ClearingHouse") == 0)
					{
						current_ClearingHouse_agent = init_ClearingHouse_agent();
						in_ClearingHouse_agent = 1;
					}
					else if(strcmp(agentname, "NSA") == 0)
					{
						current_NSA_agent = init_NSA_agent();
						in_NSA_agent = 1;
					}
					else
					{
						printf("Warning: agent name undefined - '%s'\n", agentname);
						exit(0);
					}
				}
				else if(in_Firm_agent == 1)
				{
					if(in_id) { current_Firm_agent->id = atoi(buffer); }
					if(in_region_id) { current_Firm_agent->region_id = atoi(buffer); }
					if(in_gov_id) { current_Firm_agent->gov_id = atoi(buffer); }
					if(in_day_of_month_to_act) { current_Firm_agent->day_of_month_to_act = atoi(buffer); }
					if(in_last_day_of_month_to_act) { current_Firm_agent->last_day_of_month_to_act = atoi(buffer); }
					if(in_payment_account) { current_Firm_agent->payment_account = atof(buffer); }
					if(in_payment_account_balance_sheet) { current_Firm_agent->payment_account_balance_sheet = atof(buffer); }
					if(in_bank_id) { current_Firm_agent->bank_id = atoi(buffer); }
					if(in_partition_id) { current_Firm_agent->partition_id = atoi(buffer); }
					if(in_init_transient_period) { current_Firm_agent->init_transient_period = atoi(buffer); }
					if(in_cpi) { current_Firm_agent->cpi = atof(buffer); }
					if(in_mean_wage) { current_Firm_agent->mean_wage = atof(buffer); }
					if(in_total_mean_wage) { current_Firm_agent->total_mean_wage = atof(buffer); }
					if(in_mean_wage_r_and_d) { current_Firm_agent->mean_wage_r_and_d = atof(buffer); }
					if(in_needed_capital_stock) { current_Firm_agent->needed_capital_stock = atof(buffer); }
					if(in_stock) { current_Firm_agent->stock = atof(buffer); }
					if(in_critical_stock) { current_Firm_agent->critical_stock = atof(buffer); }
					if(in_actual_cap_price) { current_Firm_agent->actual_cap_price = atof(buffer); }
					if(in_mean_specific_skills) { current_Firm_agent->mean_specific_skills = atof(buffer); }
					if(in_planned_production_quantity) { current_Firm_agent->planned_production_quantity = atof(buffer); }
					if(in_production_quantity) { current_Firm_agent->production_quantity = atof(buffer); }
					if(in_planned_output) { current_Firm_agent->planned_output = atof(buffer); }
					if(in_output) { current_Firm_agent->output = atof(buffer); }
					if(in_unit_costs) { current_Firm_agent->unit_costs = atof(buffer); }
					if(in_total_supply) { current_Firm_agent->total_supply = atof(buffer); }
					if(in_production_costs) { current_Firm_agent->production_costs = atof(buffer); }
					if(in_total_buffer) { current_Firm_agent->total_buffer = atof(buffer); }
					if(in_revenue_per_day) { current_Firm_agent->revenue_per_day = atof(buffer); }
					if(in_technological_frontier) { current_Firm_agent->technological_frontier = atof(buffer); }
					if(in_technology_vintages) { j = 0;
						rc = read_adt_technology_vintages_dynamic_array(buffer, index, &j, &current_Firm_agent->technology_vintages);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'technology_vintages' of type 'adt_technology_vintages_array'\n"); exit(0); } }
					if(in_vintage_selected) { current_Firm_agent->vintage_selected = atoi(buffer); }
					if(in_initial_technology) { current_Firm_agent->initial_technology = atof(buffer); }
					if(in_utilization_capacity) { current_Firm_agent->utilization_capacity = atof(buffer); }
					if(in_cum_revenue) { current_Firm_agent->cum_revenue = atof(buffer); }
					if(in_malls_sales_statistics) { j = 0;
						rc = read_sales_statistics_dynamic_array(buffer, index, &j, &current_Firm_agent->malls_sales_statistics);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'malls_sales_statistics' of type 'sales_statistics_array'\n"); exit(0); } }
					if(in_quality) { current_Firm_agent->quality = atof(buffer); }
					if(in_price) { current_Firm_agent->price = atof(buffer); }
					if(in_price_last_month) { current_Firm_agent->price_last_month = atof(buffer); }
					if(in_actual_mark_up) { current_Firm_agent->actual_mark_up = atof(buffer); }
					if(in_demand_capital_stock) { current_Firm_agent->demand_capital_stock = atof(buffer); }
					if(in_effective_investments) { current_Firm_agent->effective_investments = atof(buffer); }
					if(in_effective_capital_stock) { current_Firm_agent->effective_capital_stock = atof(buffer); }
					if(in_planned_production_costs) { current_Firm_agent->planned_production_costs = atof(buffer); }
					if(in_labour_costs_production) { current_Firm_agent->labour_costs_production = atof(buffer); }
					if(in_labour_costs_innovation) { current_Firm_agent->labour_costs_innovation = atof(buffer); }
					if(in_intermediate_quality_level_developing) { current_Firm_agent->intermediate_quality_level_developing = atof(buffer); }
					if(in_adaption_production_volume_due_to_insufficient_finances) { current_Firm_agent->adaption_production_volume_due_to_insufficient_finances = atof(buffer); }
					if(in_sold_quantities) { j = 0;
						rc = read_sold_quantities_per_mall_dynamic_array(buffer, index, &j, &current_Firm_agent->sold_quantities);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'sold_quantities' of type 'sold_quantities_per_mall_array'\n"); exit(0); } }
					if(in_total_sold_quantity) { current_Firm_agent->total_sold_quantity = atof(buffer); }
					if(in_cum_total_sold_quantity) { current_Firm_agent->cum_total_sold_quantity = atof(buffer); }
					if(in_sold_quantity_in_calendar_month) { current_Firm_agent->sold_quantity_in_calendar_month = atof(buffer); }
					if(in_delivery_volume) { j = 0;
						rc = read_delivery_volume_per_mall_dynamic_array(buffer, index, &j, &current_Firm_agent->delivery_volume);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'delivery_volume' of type 'delivery_volume_per_mall_array'\n"); exit(0); } }
					if(in_planned_delivery_volume) { j = 0;
						rc = read_delivery_volume_per_mall_dynamic_array(buffer, index, &j, &current_Firm_agent->planned_delivery_volume);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'planned_delivery_volume' of type 'delivery_volume_per_mall_array'\n"); exit(0); } }
					if(in_current_mall_stocks) { j = 0;
						rc = read_mall_info_dynamic_array(buffer, index, &j, &current_Firm_agent->current_mall_stocks);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'current_mall_stocks' of type 'mall_info_array'\n"); exit(0); } }
					if(in_last_planned_production_quantities) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Firm_agent->last_planned_production_quantities);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'last_planned_production_quantities' of type 'double_array'\n"); exit(0); } }
					if(in_total_external_financing_obtained) { current_Firm_agent->total_external_financing_obtained = atof(buffer); }
					if(in_capital_costs) { current_Firm_agent->capital_costs = atof(buffer); }
					if(in_employees_needed_production) { current_Firm_agent->employees_needed_production = atoi(buffer); }
					if(in_no_employees_production) { current_Firm_agent->no_employees_production = atoi(buffer); }
					if(in_planned_innovation_expenditures) { current_Firm_agent->planned_innovation_expenditures = atof(buffer); }
					if(in_planned_expenditures_production_innovation) { current_Firm_agent->planned_expenditures_production_innovation = atof(buffer); }
					if(in_labour_costs) { current_Firm_agent->labour_costs = atof(buffer); }
					if(in_capital_stock_vintages) { j = 0;
						rc = read_adt_capital_stock_vintages_dynamic_array(buffer, index, &j, &current_Firm_agent->capital_stock_vintages);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'capital_stock_vintages' of type 'adt_capital_stock_vintages_array'\n"); exit(0); } }
					if(in_vintage_choice_taken) { current_Firm_agent->vintage_choice_taken = atoi(buffer); }
					if(in_capital_financing) { j = 0;
						rc = read_financing_capital_dynamic_array(buffer, index, &j, &current_Firm_agent->capital_financing);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'capital_financing' of type 'financing_capital_array'\n"); exit(0); } }
					if(in_financial_resources_for_production) { current_Firm_agent->financial_resources_for_production = atof(buffer); }
					if(in_total_units_local_inventory) { current_Firm_agent->total_units_local_inventory = atof(buffer); }
					if(in_calc_capital_costs) { current_Firm_agent->calc_capital_costs = atof(buffer); }
					if(in_calc_production_costs) { current_Firm_agent->calc_production_costs = atof(buffer); }
					if(in_firm_productivity) { current_Firm_agent->firm_productivity = atof(buffer); }
					if(in_total_productivity_capital_stock) { current_Firm_agent->total_productivity_capital_stock = atof(buffer); }
					if(in_firm_productivity_last_year) { current_Firm_agent->firm_productivity_last_year = atof(buffer); }
					if(in_firm_productivity_progress) { current_Firm_agent->firm_productivity_progress = atof(buffer); }
					if(in_sold_quantity_in_last_calendar_month) { current_Firm_agent->sold_quantity_in_last_calendar_month = atof(buffer); }
					if(in_last_sold_quantities) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Firm_agent->last_sold_quantities);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'last_sold_quantities' of type 'double_array'\n"); exit(0); } }
					if(in_last_revenues) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Firm_agent->last_revenues);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'last_revenues' of type 'double_array'\n"); exit(0); } }
					if(in_set_of_lenders) { j = 0;
						rc = read_int_dynamic_array(buffer, index, &j, &current_Firm_agent->set_of_lenders);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'set_of_lenders' of type 'int_array'\n"); exit(0); } }
					if(in_potential_lenders) { j = 0;
						rc = read_int_dynamic_array(buffer, index, &j, &current_Firm_agent->potential_lenders);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'potential_lenders' of type 'int_array'\n"); exit(0); } }
					if(in_number_of_banks_asked) { current_Firm_agent->number_of_banks_asked = atoi(buffer); }
					if(in_received_interest_daily) { current_Firm_agent->received_interest_daily = atof(buffer); }
					if(in_received_interest_in_calendar_month) { current_Firm_agent->received_interest_in_calendar_month = atof(buffer); }
					if(in_flag_illiquidity_correction) { current_Firm_agent->flag_illiquidity_correction = atoi(buffer); }
					if(in_ebit) { current_Firm_agent->ebit = atof(buffer); }
					if(in_earnings) { current_Firm_agent->earnings = atof(buffer); }
					if(in_tax_rate_corporate) { current_Firm_agent->tax_rate_corporate = atof(buffer); }
					if(in_tax_rate_vat) { current_Firm_agent->tax_rate_vat = atof(buffer); }
					if(in_tax_payment) { current_Firm_agent->tax_payment = atof(buffer); }
					if(in_tax_payment_in_calendar_month) { current_Firm_agent->tax_payment_in_calendar_month = atof(buffer); }
					if(in_net_earnings) { current_Firm_agent->net_earnings = atof(buffer); }
					if(in_earnings_history) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Firm_agent->earnings_history);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'earnings_history' of type 'double_array'\n"); exit(0); } }
					if(in_previous_net_earnings) { current_Firm_agent->previous_net_earnings = atof(buffer); }
					if(in_total_interest_payment) { current_Firm_agent->total_interest_payment = atof(buffer); }
					if(in_total_interest_payment_in_calendar_month) { current_Firm_agent->total_interest_payment_in_calendar_month = atof(buffer); }
					if(in_total_debt_installment_payment) { current_Firm_agent->total_debt_installment_payment = atof(buffer); }
					if(in_total_debt_installment_payment_in_calendar_month) { current_Firm_agent->total_debt_installment_payment_in_calendar_month = atof(buffer); }
					if(in_total_dividend_payment) { current_Firm_agent->total_dividend_payment = atof(buffer); }
					if(in_total_dividend_payment_in_calendar_month) { current_Firm_agent->total_dividend_payment_in_calendar_month = atof(buffer); }
					if(in_flag_full_dividend) { current_Firm_agent->flag_full_dividend = atoi(buffer); }
					if(in_current_share_price) { current_Firm_agent->current_share_price = atof(buffer); }
					if(in_previous_dividend_per_share) { current_Firm_agent->previous_dividend_per_share = atof(buffer); }
					if(in_current_dividend_per_share) { current_Firm_agent->current_dividend_per_share = atof(buffer); }
					if(in_previous_earnings_per_share) { current_Firm_agent->previous_earnings_per_share = atof(buffer); }
					if(in_current_earnings_per_share) { current_Firm_agent->current_earnings_per_share = atof(buffer); }
					if(in_previous_dividend_per_earnings) { current_Firm_agent->previous_dividend_per_earnings = atof(buffer); }
					if(in_current_dividend_per_earnings) { current_Firm_agent->current_dividend_per_earnings = atof(buffer); }
					if(in_debt_earnings_ratio) { current_Firm_agent->debt_earnings_ratio = atof(buffer); }
					if(in_debt_equity_ratio) { current_Firm_agent->debt_equity_ratio = atof(buffer); }
					if(in_price_earnings_ratio) { current_Firm_agent->price_earnings_ratio = atof(buffer); }
					if(in_retained_earnings_ratio) { current_Firm_agent->retained_earnings_ratio = atof(buffer); }
					if(in_earnings_per_share_ratio_growth) { current_Firm_agent->earnings_per_share_ratio_growth = atof(buffer); }
					if(in_critical_price_earnings_ratio) { current_Firm_agent->critical_price_earnings_ratio = atof(buffer); }
					if(in_critical_earnings_per_share_ratio) { current_Firm_agent->critical_earnings_per_share_ratio = atof(buffer); }
					if(in_loans) { j = 0;
						rc = read_debt_item_dynamic_array(buffer, index, &j, &current_Firm_agent->loans);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'loans' of type 'debt_item_array'\n"); exit(0); } }
					if(in_total_debt) { current_Firm_agent->total_debt = atof(buffer); }
					if(in_target_debt) { current_Firm_agent->target_debt = atof(buffer); }
					if(in_total_debt_balance_sheet) { current_Firm_agent->total_debt_balance_sheet = atof(buffer); }
					if(in_total_value_local_inventory) { current_Firm_agent->total_value_local_inventory = atof(buffer); }
					if(in_total_value_local_inventory_balance_sheet) { current_Firm_agent->total_value_local_inventory_balance_sheet = atof(buffer); }
					if(in_total_units_capital_stock) { current_Firm_agent->total_units_capital_stock = atof(buffer); }
					if(in_total_value_capital_stock) { current_Firm_agent->total_value_capital_stock = atof(buffer); }
					if(in_total_value_capital_stock_balance_sheet) { current_Firm_agent->total_value_capital_stock_balance_sheet = atof(buffer); }
					if(in_total_capital_depreciation_value) { current_Firm_agent->total_capital_depreciation_value = atof(buffer); }
					if(in_total_capital_depreciation_units) { current_Firm_agent->total_capital_depreciation_units = atof(buffer); }
					if(in_total_assets) { current_Firm_agent->total_assets = atof(buffer); }
					if(in_equity) { current_Firm_agent->equity = atof(buffer); }
					if(in_equity_balance_sheet) { current_Firm_agent->equity_balance_sheet = atof(buffer); }
					if(in_production_liquidity_needs) { current_Firm_agent->production_liquidity_needs = atof(buffer); }
					if(in_financial_liquidity_needs) { current_Firm_agent->financial_liquidity_needs = atof(buffer); }
					if(in_total_financial_needs) { current_Firm_agent->total_financial_needs = atof(buffer); }
					if(in_external_financial_needs) { current_Firm_agent->external_financial_needs = atof(buffer); }
					if(in_earnings_per_share) { current_Firm_agent->earnings_per_share = atof(buffer); }
					if(in_retained_earnings) { current_Firm_agent->retained_earnings = atof(buffer); }
					if(in_total_payments) { current_Firm_agent->total_payments = atof(buffer); }
					if(in_previous_shares_outstanding) { current_Firm_agent->previous_shares_outstanding = atoi(buffer); }
					if(in_minsky_state) { current_Firm_agent->minsky_state = atoi(buffer); }
					if(in_minsky_state_1) { current_Firm_agent->minsky_state_1 = atoi(buffer); }
					if(in_minsky_state_2) { current_Firm_agent->minsky_state_2 = atoi(buffer); }
					if(in_minsky_state_3) { current_Firm_agent->minsky_state_3 = atoi(buffer); }
					if(in_minsky_state_4) { current_Firm_agent->minsky_state_4 = atoi(buffer); }
					if(in_minsky_state_5) { current_Firm_agent->minsky_state_5 = atoi(buffer); }
					if(in_minsky_state_20) { current_Firm_agent->minsky_state_20 = atoi(buffer); }
					if(in_minsky_state_21) { current_Firm_agent->minsky_state_21 = atoi(buffer); }
					if(in_minsky_state_22) { current_Firm_agent->minsky_state_22 = atoi(buffer); }
					if(in_minsky_state_23) { current_Firm_agent->minsky_state_23 = atoi(buffer); }
					if(in_minsky_state_30) { current_Firm_agent->minsky_state_30 = atoi(buffer); }
					if(in_minsky_state_31) { current_Firm_agent->minsky_state_31 = atoi(buffer); }
					if(in_minsky_state_32) { current_Firm_agent->minsky_state_32 = atoi(buffer); }
					if(in_minsky_state_33) { current_Firm_agent->minsky_state_33 = atoi(buffer); }
					if(in_minsky_state_40) { current_Firm_agent->minsky_state_40 = atoi(buffer); }
					if(in_minsky_state_41) { current_Firm_agent->minsky_state_41 = atoi(buffer); }
					if(in_minsky_state_42) { current_Firm_agent->minsky_state_42 = atoi(buffer); }
					if(in_minsky_state_43) { current_Firm_agent->minsky_state_43 = atoi(buffer); }
					if(in_age_at_bankruptcy) { current_Firm_agent->age_at_bankruptcy = atoi(buffer); }
					if(in_debt_at_bankruptcy) { current_Firm_agent->debt_at_bankruptcy = atof(buffer); }
					if(in_equity_at_bankruptcy) { current_Firm_agent->equity_at_bankruptcy = atof(buffer); }
					if(in_no_employees_at_bankruptcy) { current_Firm_agent->no_employees_at_bankruptcy = atoi(buffer); }
					if(in_equity_asset_ratio) { current_Firm_agent->equity_asset_ratio = atof(buffer); }
					if(in_profit_asset_ratio) { current_Firm_agent->profit_asset_ratio = atof(buffer); }
					if(in_sales_asset_ratio) { current_Firm_agent->sales_asset_ratio = atof(buffer); }
					if(in_investment_asset_ratio) { current_Firm_agent->investment_asset_ratio = atof(buffer); }
					if(in_total_income) { current_Firm_agent->total_income = atof(buffer); }
					if(in_total_liabilities) { current_Firm_agent->total_liabilities = atof(buffer); }
					if(in_total_expenses) { current_Firm_agent->total_expenses = atof(buffer); }
					if(in_current_shares_outstanding) { current_Firm_agent->current_shares_outstanding = atoi(buffer); }
					if(in_employees) { j = 0;
						rc = read_employee_dynamic_array(buffer, index, &j, &current_Firm_agent->employees);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'employees' of type 'employee_array'\n"); exit(0); } }
					if(in_r_and_d_employees) { j = 0;
						rc = read_employee_dynamic_array(buffer, index, &j, &current_Firm_agent->r_and_d_employees);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'r_and_d_employees' of type 'employee_array'\n"); exit(0); } }
					if(in_wage_offer) { current_Firm_agent->wage_offer = atof(buffer); }
					if(in_technology) { current_Firm_agent->technology = atof(buffer); }
					if(in_no_employees) { current_Firm_agent->no_employees = atoi(buffer); }
					if(in_no_employees_skill_1) { current_Firm_agent->no_employees_skill_1 = atoi(buffer); }
					if(in_no_employees_skill_2) { current_Firm_agent->no_employees_skill_2 = atoi(buffer); }
					if(in_no_employees_skill_3) { current_Firm_agent->no_employees_skill_3 = atoi(buffer); }
					if(in_no_employees_skill_4) { current_Firm_agent->no_employees_skill_4 = atoi(buffer); }
					if(in_no_employees_skill_5) { current_Firm_agent->no_employees_skill_5 = atoi(buffer); }
					if(in_vacancies) { current_Firm_agent->vacancies = atoi(buffer); }
					if(in_no_redundancies) { current_Firm_agent->no_redundancies = atoi(buffer); }
					if(in_no_redundancies_r_and_d_employees) { current_Firm_agent->no_redundancies_r_and_d_employees = atoi(buffer); }
					if(in_vacancies_r_and_d_employees) { current_Firm_agent->vacancies_r_and_d_employees = atoi(buffer); }
					if(in_posted_vacancies) { current_Firm_agent->posted_vacancies = atoi(buffer); }
					if(in_posted_vacancies_r_and_d_employees) { current_Firm_agent->posted_vacancies_r_and_d_employees = atoi(buffer); }
					if(in_average_g_skill) { current_Firm_agent->average_g_skill = atof(buffer); }
					if(in_average_adaptation_speed_specific_skills) { current_Firm_agent->average_adaptation_speed_specific_skills = atof(buffer); }
					if(in_list_adaptation_speed_per_skill_group) { j = 0;
						rc = read_adt_list_adaptation_speed_dynamic_array(buffer, index, &j, &current_Firm_agent->list_adaptation_speed_per_skill_group);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'list_adaptation_speed_per_skill_group' of type 'adt_list_adaptation_speed_array'\n"); exit(0); } }
					if(in_average_s_skill_of_1) { current_Firm_agent->average_s_skill_of_1 = atof(buffer); }
					if(in_average_s_skill_of_2) { current_Firm_agent->average_s_skill_of_2 = atof(buffer); }
					if(in_average_s_skill_of_3) { current_Firm_agent->average_s_skill_of_3 = atof(buffer); }
					if(in_average_s_skill_of_4) { current_Firm_agent->average_s_skill_of_4 = atof(buffer); }
					if(in_average_s_skill_of_5) { current_Firm_agent->average_s_skill_of_5 = atof(buffer); }
					if(in_wage_offer_for_skill_1) { current_Firm_agent->wage_offer_for_skill_1 = atof(buffer); }
					if(in_wage_offer_for_skill_2) { current_Firm_agent->wage_offer_for_skill_2 = atof(buffer); }
					if(in_wage_offer_for_skill_3) { current_Firm_agent->wage_offer_for_skill_3 = atof(buffer); }
					if(in_wage_offer_for_skill_4) { current_Firm_agent->wage_offer_for_skill_4 = atof(buffer); }
					if(in_wage_offer_for_skill_5) { current_Firm_agent->wage_offer_for_skill_5 = atof(buffer); }
					if(in_wage_offer_for_r_and_d_employees) { current_Firm_agent->wage_offer_for_r_and_d_employees = atof(buffer); }
					if(in_base_wage_offer_r_and_d) { current_Firm_agent->base_wage_offer_r_and_d = atof(buffer); }
					if(in_employees_needed) { current_Firm_agent->employees_needed = atoi(buffer); }
					if(in_firm_balance_sheet_calendar) { j = 0;
						rc = read_firm_balance_sheet_adt(buffer, index, &j, &current_Firm_agent->firm_balance_sheet_calendar);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'firm_balance_sheet_calendar' of type 'firm_balance_sheet_adt'\n"); exit(0); } }
					if(in_firm_stocks_calendar) { j = 0;
						rc = read_firm_stocks_adt(buffer, index, &j, &current_Firm_agent->firm_stocks_calendar);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'firm_stocks_calendar' of type 'firm_stocks_adt'\n"); exit(0); } }
					if(in_firm_outflows_calendar) { j = 0;
						rc = read_firm_outflows_adt(buffer, index, &j, &current_Firm_agent->firm_outflows_calendar);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'firm_outflows_calendar' of type 'firm_outflows_adt'\n"); exit(0); } }
					if(in_firm_inflows_calendar) { j = 0;
						rc = read_firm_inflows_adt(buffer, index, &j, &current_Firm_agent->firm_inflows_calendar);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'firm_inflows_calendar' of type 'firm_inflows_adt'\n"); exit(0); } }
					if(in_age) { current_Firm_agent->age = atoi(buffer); }
					if(in_transfer_payment) { current_Firm_agent->transfer_payment = atof(buffer); }
					if(in_subsidy_pct) { current_Firm_agent->subsidy_pct = atof(buffer); }
					if(in_active) { current_Firm_agent->active = atoi(buffer); }
					if(in_inactive) { current_Firm_agent->inactive = atoi(buffer); }
					if(in_zero_output) { current_Firm_agent->zero_output = atoi(buffer); }
					if(in_bankruptcy_idle_counter) { current_Firm_agent->bankruptcy_idle_counter = atoi(buffer); }
					if(in_bankruptcy_state) { current_Firm_agent->bankruptcy_state = atoi(buffer); }
					if(in_bankruptcy_insolvency_state) { current_Firm_agent->bankruptcy_insolvency_state = atoi(buffer); }
					if(in_bankruptcy_illiquidity_state) { current_Firm_agent->bankruptcy_illiquidity_state = atoi(buffer); }
					if(in_financial_crisis_state) { current_Firm_agent->financial_crisis_state = atoi(buffer); }
					if(in_average_s_skill_from_eurostat) { current_Firm_agent->average_s_skill_from_eurostat = atof(buffer); }
					if(in_average_output_from_eurostat) { current_Firm_agent->average_output_from_eurostat = atof(buffer); }
					if(in_subsidy_payment) { current_Firm_agent->subsidy_payment = atof(buffer); }
					if(in_current_price_index) { current_Firm_agent->current_price_index = atof(buffer); }
					if(in_current_quality_index) { current_Firm_agent->current_quality_index = atof(buffer); }
					if(in_no_competitors) { current_Firm_agent->no_competitors = atoi(buffer); }
					if(in_indicator_earnings) { current_Firm_agent->indicator_earnings = atoi(buffer); }
					if(in_indicator_capital_costs) { current_Firm_agent->indicator_capital_costs = atoi(buffer); }
					if(in_indicator_size_by_capital_stock) { current_Firm_agent->indicator_size_by_capital_stock = atoi(buffer); }
					if(in_market_research_sample_size) { current_Firm_agent->market_research_sample_size = atoi(buffer); }
					if(in_product_innovation) { current_Firm_agent->product_innovation = atoi(buffer); }
					if(in_regional_analysis) { current_Firm_agent->regional_analysis = atoi(buffer); }
					if(in_day_of_year_market_research) { current_Firm_agent->day_of_year_market_research = atoi(buffer); }
					if(in_actual_sample_size) { current_Firm_agent->actual_sample_size = atoi(buffer); }
					if(in_last_market_sizes) { j = 0;
						rc = read_dt_total_and_regional_market_size_dynamic_array(buffer, index, &j, &current_Firm_agent->last_market_sizes);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'last_market_sizes' of type 'dt_total_and_regional_market_size_array'\n"); exit(0); } }
					if(in_price_range_pricing) { j = 0;
						rc = read_dt_price_range(buffer, index, &j, &current_Firm_agent->price_range_pricing);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'price_range_pricing' of type 'dt_price_range'\n"); exit(0); } }
					if(in_price_range_innovation) { j = 0;
						rc = read_dt_price_range(buffer, index, &j, &current_Firm_agent->price_range_innovation);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'price_range_innovation' of type 'dt_price_range'\n"); exit(0); } }
					if(in_new_product_released) { current_Firm_agent->new_product_released = atoi(buffer); }
					if(in_prospective_variables) { j = 0;
						rc = read_dt_prospective_variables_dynamic_array(buffer, index, &j, &current_Firm_agent->prospective_variables);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'prospective_variables' of type 'dt_prospective_variables_array'\n"); exit(0); } }
					if(in_price_at_questionnaire) { current_Firm_agent->price_at_questionnaire = atof(buffer); }
					if(in_price_index_at_questionnaire) { current_Firm_agent->price_index_at_questionnaire = atof(buffer); }
					if(in_best_pricing_strategies) { j = 0;
						rc = read_dt_best_price_strategies_dynamic_array(buffer, index, &j, &current_Firm_agent->best_pricing_strategies);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'best_pricing_strategies' of type 'dt_best_price_strategies_array'\n"); exit(0); } }
					if(in_best_pricing_abandon_strategy) { j = 0;
						rc = read_dt_best_price_strategies(buffer, index, &j, &current_Firm_agent->best_pricing_abandon_strategy);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'best_pricing_abandon_strategy' of type 'dt_best_price_strategies'\n"); exit(0); } }
					if(in_intermediate_quality) { current_Firm_agent->intermediate_quality = atof(buffer); }
					if(in_no_employees_product_innovation_fundable) { current_Firm_agent->no_employees_product_innovation_fundable = atoi(buffer); }
					if(in_r_and_d_probability_for_incremental_success) { current_Firm_agent->r_and_d_probability_for_incremental_success = atof(buffer); }
					if(in_market_research_active) { current_Firm_agent->market_research_active = atoi(buffer); }
					if(in_innovation_successful) { current_Firm_agent->innovation_successful = atoi(buffer); }
					if(in_actual_market_share) { current_Firm_agent->actual_market_share = atof(buffer); }
					if(in_market_size) { current_Firm_agent->market_size = atof(buffer); }
					if(in_estimated_market_size) { current_Firm_agent->estimated_market_size = atof(buffer); }
					if(in_linear_regression_estimators) { j = 0;
						rc = read_estimators_linear_regression_dynamic_array(buffer, index, &j, &current_Firm_agent->linear_regression_estimators);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'linear_regression_estimators' of type 'estimators_linear_regression_array'\n"); exit(0); } }
					if(in_linear_regression_market_size) { j = 0;
						rc = read_estimators_linear_regression_dynamic_array(buffer, index, &j, &current_Firm_agent->linear_regression_market_size);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'linear_regression_market_size' of type 'estimators_linear_regression_array'\n"); exit(0); } }
					if(in_counter_month_since_last_price_setting) { current_Firm_agent->counter_month_since_last_price_setting = atoi(buffer); }
					if(in_demand_function_pricing) { j = 0;
						rc = read_dt_demand_function(buffer, index, &j, &current_Firm_agent->demand_function_pricing);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'demand_function_pricing' of type 'dt_demand_function'\n"); exit(0); } }
					if(in_demand_functions_product_innovation) { j = 0;
						rc = read_dt_demand_function_dynamic_array(buffer, index, &j, &current_Firm_agent->demand_functions_product_innovation);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'demand_functions_product_innovation' of type 'dt_demand_function_array'\n"); exit(0); } }
					if(in_market_research_delayed) { current_Firm_agent->market_research_delayed = atoi(buffer); }
					if(in_market_research_data_pricing) { j = 0;
						rc = read_dt_market_research_price_dynamic_array(buffer, index, &j, &current_Firm_agent->market_research_data_pricing);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'market_research_data_pricing' of type 'dt_market_research_price_array'\n"); exit(0); } }
					if(in_market_research_data_product_innovation) { j = 0;
						rc = read_dt_market_research_qualities_dynamic_array(buffer, index, &j, &current_Firm_agent->market_research_data_product_innovation);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'market_research_data_product_innovation' of type 'dt_market_research_qualities_array'\n"); exit(0); } }
					if(in_expected_earnings_per_month) { current_Firm_agent->expected_earnings_per_month = atof(buffer); }
					if(in_expected_price_choices) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Firm_agent->expected_price_choices);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'expected_price_choices' of type 'double_array'\n"); exit(0); } }
					if(in_no_considered_qualities) { current_Firm_agent->no_considered_qualities = atof(buffer); }
					if(in_last_interest_rate_for_loans) { current_Firm_agent->last_interest_rate_for_loans = atof(buffer); }
					if(in_cum_earnings_last_r_d_project) { current_Firm_agent->cum_earnings_last_r_d_project = atof(buffer); }
					if(in_cum_r_d_investments) { current_Firm_agent->cum_r_d_investments = atof(buffer); }
					if(in_r_d_investments_last_project) { current_Firm_agent->r_d_investments_last_project = atof(buffer); }
					if(in_total_person_months) { current_Firm_agent->total_person_months = atoi(buffer); }
					if(in_cum_person_months) { current_Firm_agent->cum_person_months = atoi(buffer); }
					if(in_actual_r_and_d_success_probability) { current_Firm_agent->actual_r_and_d_success_probability = atof(buffer); }
					if(in_last_quality) { current_Firm_agent->last_quality = atof(buffer); }
					if(in_quality_change) { current_Firm_agent->quality_change = atof(buffer); }
					if(in_expected_sold_quantity_per_month) { current_Firm_agent->expected_sold_quantity_per_month = atof(buffer); }
					if(in_estimated_market_share) { current_Firm_agent->estimated_market_share = atof(buffer); }
					if(in_estimated_market_share_beginning_of_year) { current_Firm_agent->estimated_market_share_beginning_of_year = atof(buffer); }
					if(in_estimated_market_share_end_of_year) { current_Firm_agent->estimated_market_share_end_of_year = atof(buffer); }
					if(in_estimated_yearly_earnings) { current_Firm_agent->estimated_yearly_earnings = atof(buffer); }
					if(in_expected_earnings_and_costs_over_year) { j = 0;
						rc = read_dt_monthly_estimations_static_array(buffer, index, &j, current_Firm_agent->expected_earnings_and_costs_over_year, 12);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'expected_earnings_and_costs_over_year' of type 'dt_monthly_estimations'\n"); exit(0); } }
					if(in_expected_output_in_current_month) { current_Firm_agent->expected_output_in_current_month = atof(buffer); }
					if(in_expected_profit_in_current_month) { current_Firm_agent->expected_profit_in_current_month = atof(buffer); }
					if(in_expected_labor_costs_in_current_month) { current_Firm_agent->expected_labor_costs_in_current_month = atof(buffer); }
					if(in_expected_capital_costs_in_current_month) { current_Firm_agent->expected_capital_costs_in_current_month = atof(buffer); }
					if(in_expected_interests_in_current_month) { current_Firm_agent->expected_interests_in_current_month = atof(buffer); }
					if(in_expected_output_in_previous_month) { current_Firm_agent->expected_output_in_previous_month = atof(buffer); }
					if(in_expected_actual_sold_quantity_in_previous_month) { current_Firm_agent->expected_actual_sold_quantity_in_previous_month = atof(buffer); }
					if(in_expected_actual_sold_quantity_in_current_month) { current_Firm_agent->expected_actual_sold_quantity_in_current_month = atof(buffer); }
					if(in_expected_labor_costs_in_previous_month) { current_Firm_agent->expected_labor_costs_in_previous_month = atof(buffer); }
					if(in_expected_capital_costs_in_previous_month) { current_Firm_agent->expected_capital_costs_in_previous_month = atof(buffer); }
					if(in_expected_interests_in_previous_month) { current_Firm_agent->expected_interests_in_previous_month = atof(buffer); }
					if(in_expected_profit_in_previous_month) { current_Firm_agent->expected_profit_in_previous_month = atof(buffer); }
					if(in_expected_wage_in_current_month) { current_Firm_agent->expected_wage_in_current_month = atof(buffer); }
					if(in_expected_wage_in_previous_month) { current_Firm_agent->expected_wage_in_previous_month = atof(buffer); }
					if(in_expected_mean_specific_skills_in_current_month) { current_Firm_agent->expected_mean_specific_skills_in_current_month = atof(buffer); }
					if(in_expected_mean_specific_skills_in_previous_month) { current_Firm_agent->expected_mean_specific_skills_in_previous_month = atof(buffer); }
					if(in_expected_average_productivity_in_current_month) { current_Firm_agent->expected_average_productivity_in_current_month = atof(buffer); }
					if(in_expected_investment_nominal_in_current_month) { current_Firm_agent->expected_investment_nominal_in_current_month = atof(buffer); }
					if(in_expected_investment_nominal_in_previous_month) { current_Firm_agent->expected_investment_nominal_in_previous_month = atof(buffer); }
					if(in_expected_average_productivity_in_previous_month) { current_Firm_agent->expected_average_productivity_in_previous_month = atof(buffer); }
					if(in_earnings_while_last_pricing_period) { current_Firm_agent->earnings_while_last_pricing_period = atof(buffer); }
					if(in_sum_earnings_since_price_change) { current_Firm_agent->sum_earnings_since_price_change = atof(buffer); }
					if(in_variables_last_year) { j = 0;
						rc = read_dt_variables_changed_dynamic_array(buffer, index, &j, &current_Firm_agent->variables_last_year);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'variables_last_year' of type 'dt_variables_changed_array'\n"); exit(0); } }
					if(in_innovation_month_counter) { current_Firm_agent->innovation_month_counter = atoi(buffer); }
					if(in_variables_change) { j = 0;
						rc = read_dt_variables_changed(buffer, index, &j, &current_Firm_agent->variables_change);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'variables_change' of type 'dt_variables_changed'\n"); exit(0); } }
					if(in_r_and_d_investments_per_month) { current_Firm_agent->r_and_d_investments_per_month = atof(buffer); }
					if(in_innovation_flag) { current_Firm_agent->innovation_flag = atoi(buffer); }
					if(in_innovation_employees_needed) { current_Firm_agent->innovation_employees_needed = atoi(buffer); }
					if(in_no_employees_innovation) { current_Firm_agent->no_employees_innovation = atoi(buffer); }
					if(in_employees_needed_innovation) { current_Firm_agent->employees_needed_innovation = atoi(buffer); }
					if(in_optimal_employees_needed_innovation) { current_Firm_agent->optimal_employees_needed_innovation = atoi(buffer); }
					if(in_total_no_periods_for_product_development) { current_Firm_agent->total_no_periods_for_product_development = atoi(buffer); }
					if(in_ratio_project_value_established_product) { current_Firm_agent->ratio_project_value_established_product = atof(buffer); }
					if(in_vintage_choice_already_taken) { current_Firm_agent->vintage_choice_already_taken = atoi(buffer); }
					if(in_change_due_to_last_innovation) { current_Firm_agent->change_due_to_last_innovation = atof(buffer); }
					if(in_remaining_periods_to_complete_product_development) { current_Firm_agent->remaining_periods_to_complete_product_development = atoi(buffer); }
					if(in_planned_quality) { current_Firm_agent->planned_quality = atof(buffer); }
					if(in_product_development_completed) { current_Firm_agent->product_development_completed = atof(buffer); }
					if(in_price_just_set_flag) { current_Firm_agent->price_just_set_flag = atof(buffer); }
					if(in_value_lattice) { j = 0;
						rc = read_dt_value_lattice_years_dynamic_array(buffer, index, &j, &current_Firm_agent->value_lattice);
						if(rc != 0) { printf("Error: reading 'Firm' agent variable 'value_lattice' of type 'dt_value_lattice_years_array'\n"); exit(0); } }
					if(in_combined_variance_demand_function) { current_Firm_agent->combined_variance_demand_function = atof(buffer); }
				 }else if(in_Household_agent == 1)
				{
					if(in_id) { current_Household_agent->id = atoi(buffer); }
					if(in_region_id) { current_Household_agent->region_id = atoi(buffer); }
					if(in_neighboring_region_ids) { j = 0;
						rc = read_int_dynamic_array(buffer, index, &j, &current_Household_agent->neighboring_region_ids);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'neighboring_region_ids' of type 'int_array'\n"); exit(0); } }
					if(in_gov_id) { current_Household_agent->gov_id = atoi(buffer); }
					if(in_day_of_month_to_act) { current_Household_agent->day_of_month_to_act = atoi(buffer); }
					if(in_payment_account) { current_Household_agent->payment_account = atof(buffer); }
					if(in_bank_id) { current_Household_agent->bank_id = atoi(buffer); }
					if(in_partition_id) { current_Household_agent->partition_id = atoi(buffer); }
					if(in_init_transient_period) { current_Household_agent->init_transient_period = atoi(buffer); }
					if(in_consumption_budget) { current_Household_agent->consumption_budget = atof(buffer); }
					if(in_housing_budget) { current_Household_agent->housing_budget = atof(buffer); }
					if(in_consumption_budget_in_month) { current_Household_agent->consumption_budget_in_month = atof(buffer); }
					if(in_week_of_month) { current_Household_agent->week_of_month = atoi(buffer); }
					if(in_weekly_budget) { current_Household_agent->weekly_budget = atof(buffer); }
					if(in_rationed) { current_Household_agent->rationed = atoi(buffer); }
					if(in_mall_completely_sold_out) { current_Household_agent->mall_completely_sold_out = atoi(buffer); }
					if(in_order_quantity) { j = 0;
						rc = read_ordered_quantity_static_array(buffer, index, &j, current_Household_agent->order_quantity, 2);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'order_quantity' of type 'ordered_quantity'\n"); exit(0); } }
					if(in_received_quantity) { j = 0;
						rc = read_received_quantities_static_array(buffer, index, &j, current_Household_agent->received_quantity, 2);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'received_quantity' of type 'received_quantities'\n"); exit(0); } }
					if(in_day_of_week_to_act) { current_Household_agent->day_of_week_to_act = atoi(buffer); }
					if(in_day_of_month_receive_income) { current_Household_agent->day_of_month_receive_income = atoi(buffer); }
					if(in_current_productivity_employer) { current_Household_agent->current_productivity_employer = atof(buffer); }
					if(in_current_mean_specific_skills_employer) { current_Household_agent->current_mean_specific_skills_employer = atof(buffer); }
					if(in_tax_payment) { current_Household_agent->tax_payment = atof(buffer); }
					if(in_cum_total_dividends) { current_Household_agent->cum_total_dividends = atof(buffer); }
					if(in_tax_rate_hh_capital) { current_Household_agent->tax_rate_hh_capital = atof(buffer); }
					if(in_tax_rate_hh_labour) { current_Household_agent->tax_rate_hh_labour = atof(buffer); }
					if(in_price_index) { current_Household_agent->price_index = atof(buffer); }
					if(in_price_index_base_period) { current_Household_agent->price_index_base_period = atof(buffer); }
					if(in_commuting_costs_price_level_weight) { current_Household_agent->commuting_costs_price_level_weight = atof(buffer); }
					if(in_expenditures) { current_Household_agent->expenditures = atof(buffer); }
					if(in_received_dividend) { current_Household_agent->received_dividend = atof(buffer); }
					if(in_received_dividend_in_calendar_month) { current_Household_agent->received_dividend_in_calendar_month = atof(buffer); }
					if(in_received_interest_daily) { current_Household_agent->received_interest_daily = atof(buffer); }
					if(in_received_interest_in_calendar_month) { current_Household_agent->received_interest_in_calendar_month = atof(buffer); }
					if(in_flag_consumption_shifting) { current_Household_agent->flag_consumption_shifting = atoi(buffer); }
					if(in_excess_weekly_budget) { current_Household_agent->excess_weekly_budget = atof(buffer); }
					if(in_wealth_income_ratio_actual) { current_Household_agent->wealth_income_ratio_actual = atof(buffer); }
					if(in_wealth_income_ratio_target) { current_Household_agent->wealth_income_ratio_target = atof(buffer); }
					if(in_last_weekly_budget) { current_Household_agent->last_weekly_budget = atof(buffer); }
					if(in_have_mortgage) { current_Household_agent->have_mortgage = atoi(buffer); }
					if(in_hmr_mortgage_status) { current_Household_agent->hmr_mortgage_status = atoi(buffer); }
					if(in_op_mortgage_status) { current_Household_agent->op_mortgage_status = atoi(buffer); }
					if(in_request_mortgage) { current_Household_agent->request_mortgage = atoi(buffer); }
					if(in_mortgage_pay_day) { current_Household_agent->mortgage_pay_day = atoi(buffer); }
					if(in_mortgage_sample_inputs) { j = 0;
						rc = read_mortgage_sample_adt_static_array(buffer, index, &j, current_Household_agent->mortgage_sample_inputs, 6);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'mortgage_sample_inputs' of type 'mortgage_sample_adt'\n"); exit(0); } }
					if(in_sample_inputs) { j = 0;
						rc = read_sample_adt(buffer, index, &j, &current_Household_agent->sample_inputs);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'sample_inputs' of type 'sample_adt'\n"); exit(0); } }
					if(in_is_tenant) { current_Household_agent->is_tenant = atoi(buffer); }
					if(in_is_owner) { current_Household_agent->is_owner = atoi(buffer); }
					if(in_is_landlord) { current_Household_agent->is_landlord = atoi(buffer); }
					if(in_plan_stay_tenant) { current_Household_agent->plan_stay_tenant = atoi(buffer); }
					if(in_plan_stay_owner) { current_Household_agent->plan_stay_owner = atoi(buffer); }
					if(in_plan_stay_landlord) { current_Household_agent->plan_stay_landlord = atoi(buffer); }
					if(in_plan_sell_hmr) { current_Household_agent->plan_sell_hmr = atoi(buffer); }
					if(in_plan_buy_hmr) { current_Household_agent->plan_buy_hmr = atoi(buffer); }
					if(in_plan_rent_hmr) { current_Household_agent->plan_rent_hmr = atoi(buffer); }
					if(in_plan_stop_rent_hmr) { current_Household_agent->plan_stop_rent_hmr = atoi(buffer); }
					if(in_plan_buy_op) { current_Household_agent->plan_buy_op = atoi(buffer); }
					if(in_plan_sell_op) { current_Household_agent->plan_sell_op = atoi(buffer); }
					if(in_plan_let_op) { current_Household_agent->plan_let_op = atoi(buffer); }
					if(in_plan_stop_let_op) { current_Household_agent->plan_stop_let_op = atoi(buffer); }
					if(in_just_sold_hmr) { current_Household_agent->just_sold_hmr = atoi(buffer); }
					if(in_just_purchased_hmr) { current_Household_agent->just_purchased_hmr = atoi(buffer); }
					if(in_just_purchased_op) { current_Household_agent->just_purchased_op = atoi(buffer); }
					if(in_just_sold_op) { current_Household_agent->just_sold_op = atoi(buffer); }
					if(in_else_state) { current_Household_agent->else_state = atoi(buffer); }
					if(in_other_states) { current_Household_agent->other_states = atoi(buffer); }
					if(in_total_dsti) { current_Household_agent->total_dsti = atof(buffer); }
					if(in_rental_unit) { j = 0;
						rc = read_rental_adt(buffer, index, &j, &current_Household_agent->rental_unit);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'rental_unit' of type 'rental_adt'\n"); exit(0); } }
					if(in_risk_free_rate) { current_Household_agent->risk_free_rate = atof(buffer); }
					if(in_wealth) { current_Household_agent->wealth = atof(buffer); }
					if(in_beliefs) { j = 0;
						rc = read_Belief(buffer, index, &j, &current_Household_agent->beliefs);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'beliefs' of type 'Belief'\n"); exit(0); } }
					if(in_assetsowned) { j = 0;
						rc = read_index_portfolio(buffer, index, &j, &current_Household_agent->assetsowned);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'assetsowned' of type 'index_portfolio'\n"); exit(0); } }
					if(in_logit_beta) { current_Household_agent->logit_beta = atof(buffer); }
					if(in_wage) { current_Household_agent->wage = atof(buffer); }
					if(in_wage_reservation) { current_Household_agent->wage_reservation = atof(buffer); }
					if(in_general_skill) { current_Household_agent->general_skill = atoi(buffer); }
					if(in_list_adaptation_speed_per_general_skill_group) { j = 0;
						rc = read_adt_list_adaptation_speed_dynamic_array(buffer, index, &j, &current_Household_agent->list_adaptation_speed_per_general_skill_group);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'list_adaptation_speed_per_general_skill_group' of type 'adt_list_adaptation_speed_array'\n"); exit(0); } }
					if(in_on_the_job_search) { current_Household_agent->on_the_job_search = atoi(buffer); }
					if(in_search_today) { current_Household_agent->search_today = atoi(buffer); }
					if(in_last_labour_income) { current_Household_agent->last_labour_income = atof(buffer); }
					if(in_specific_skill) { current_Household_agent->specific_skill = atof(buffer); }
					if(in_employee_firm_id) { current_Household_agent->employee_firm_id = atoi(buffer); }
					if(in_just_employed) { current_Household_agent->just_employed = atoi(buffer); }
					if(in_just_unemployed) { current_Household_agent->just_unemployed = atoi(buffer); }
					if(in_start_unemployed) { current_Household_agent->start_unemployed = atoi(buffer); }
					if(in_start_employed) { current_Household_agent->start_employed = atoi(buffer); }
					if(in_unemployed_duration) { current_Household_agent->unemployed_duration = atoi(buffer); }
					if(in_enter_matching) { current_Household_agent->enter_matching = atoi(buffer); }
					if(in_employer_region_id) { current_Household_agent->employer_region_id = atoi(buffer); }
					if(in_employer_igfirm) { current_Household_agent->employer_igfirm = atoi(buffer); }
					if(in_day_of_month_receive_benefit) { current_Household_agent->day_of_month_receive_benefit = atoi(buffer); }
					if(in_unemployment_payment) { current_Household_agent->unemployment_payment = atof(buffer); }
					if(in_region_wide_mean_wage) { current_Household_agent->region_wide_mean_wage = atof(buffer); }
					if(in_last_net_income) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Household_agent->last_net_income);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'last_net_income' of type 'double_array'\n"); exit(0); } }
					if(in_mean_net_income) { current_Household_agent->mean_net_income = atof(buffer); }
					if(in_monthly_income_vector) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Household_agent->monthly_income_vector);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'monthly_income_vector' of type 'double_array'\n"); exit(0); } }
					if(in_quarterly_income_vector) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Household_agent->quarterly_income_vector);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'quarterly_income_vector' of type 'double_array'\n"); exit(0); } }
					if(in_total_gross_monthly_income) { current_Household_agent->total_gross_monthly_income = atof(buffer); }
					if(in_total_gross_quarterly_income) { current_Household_agent->total_gross_quarterly_income = atof(buffer); }
					if(in_household_balance_sheet_calendar) { j = 0;
						rc = read_household_balance_sheet_adt(buffer, index, &j, &current_Household_agent->household_balance_sheet_calendar);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'household_balance_sheet_calendar' of type 'household_balance_sheet_adt'\n"); exit(0); } }
					if(in_household_stocks_calendar) { j = 0;
						rc = read_household_stocks_adt(buffer, index, &j, &current_Household_agent->household_stocks_calendar);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'household_stocks_calendar' of type 'household_stocks_adt'\n"); exit(0); } }
					if(in_household_outflows_calendar) { j = 0;
						rc = read_household_outflows_adt(buffer, index, &j, &current_Household_agent->household_outflows_calendar);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'household_outflows_calendar' of type 'household_outflows_adt'\n"); exit(0); } }
					if(in_household_inflows_calendar) { j = 0;
						rc = read_household_inflows_adt(buffer, index, &j, &current_Household_agent->household_inflows_calendar);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'household_inflows_calendar' of type 'household_inflows_adt'\n"); exit(0); } }
					if(in_unemployment_benefit_pct) { current_Household_agent->unemployment_benefit_pct = atof(buffer); }
					if(in_transfer_payment) { current_Household_agent->transfer_payment = atof(buffer); }
					if(in_subsidy_pct) { current_Household_agent->subsidy_pct = atof(buffer); }
					if(in_total_income) { current_Household_agent->total_income = atof(buffer); }
					if(in_total_expenses) { current_Household_agent->total_expenses = atof(buffer); }
					if(in_total_assets) { current_Household_agent->total_assets = atof(buffer); }
					if(in_total_liabilities) { current_Household_agent->total_liabilities = atof(buffer); }
					if(in_monthly_consumption_expenditure) { current_Household_agent->monthly_consumption_expenditure = atof(buffer); }
					if(in_monthly_bond_interest_income) { current_Household_agent->monthly_bond_interest_income = atof(buffer); }
					if(in_subsidy_payment) { current_Household_agent->subsidy_payment = atof(buffer); }
					if(in_region_mean_wage) { current_Household_agent->region_mean_wage = atof(buffer); }
					if(in_human_capital_policy_flag) { current_Household_agent->human_capital_policy_flag = atoi(buffer); }
					if(in_questionnaire_attending_propability) { current_Household_agent->questionnaire_attending_propability = atof(buffer); }
					if(in_willingness_to_attend) { current_Household_agent->willingness_to_attend = atoi(buffer); }
					if(in_interviewer_id) { current_Household_agent->interviewer_id = atoi(buffer); }
					if(in_random_no_test) { current_Household_agent->random_no_test = atoi(buffer); }
					if(in_questionnaire) { j = 0;
						rc = read_int_static_array(buffer, index, &j, current_Household_agent->questionnaire, 40);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'questionnaire' of type 'int'\n"); exit(0); } }
					if(in_current_price_quality_list) { j = 0;
						rc = read_consumption_goods_offer_dynamic_array(buffer, index, &j, &current_Household_agent->current_price_quality_list);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'current_price_quality_list' of type 'consumption_goods_offer_array'\n"); exit(0); } }
					if(in_housing_bid_price) { current_Household_agent->housing_bid_price = atof(buffer); }
					if(in_housing_ask_price) { current_Household_agent->housing_ask_price = atof(buffer); }
					if(in_house) { j = 0;
						rc = read_house_adt(buffer, index, &j, &current_Household_agent->house);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'house' of type 'house_adt'\n"); exit(0); } }
					if(in_rent_bid_price) { current_Household_agent->rent_bid_price = atof(buffer); }
					if(in_rent_ask_price) { current_Household_agent->rent_ask_price = atof(buffer); }
					if(in_hmr_price_index) { j = 0;
						rc = read_price_index_adt(buffer, index, &j, &current_Household_agent->hmr_price_index);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'hmr_price_index' of type 'price_index_adt'\n"); exit(0); } }
					if(in_op_price_index) { j = 0;
						rc = read_price_index_adt(buffer, index, &j, &current_Household_agent->op_price_index);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'op_price_index' of type 'price_index_adt'\n"); exit(0); } }
					if(in_rent_price_index) { j = 0;
						rc = read_price_index_adt(buffer, index, &j, &current_Household_agent->rent_price_index);
						if(rc != 0) { printf("Error: reading 'Household' agent variable 'rent_price_index' of type 'price_index_adt'\n"); exit(0); } }
				 }else if(in_Mall_agent == 1)
				{
					if(in_id) { current_Mall_agent->id = atoi(buffer); }
					if(in_region_id) { current_Mall_agent->region_id = atoi(buffer); }
					if(in_gov_id) { current_Mall_agent->gov_id = atoi(buffer); }
					if(in_partition_id) { current_Mall_agent->partition_id = atoi(buffer); }
					if(in_init_transient_period) { current_Mall_agent->init_transient_period = atoi(buffer); }
					if(in_current_stock) { j = 0;
						rc = read_mall_stock_dynamic_array(buffer, index, &j, &current_Mall_agent->current_stock);
						if(rc != 0) { printf("Error: reading 'Mall' agent variable 'current_stock' of type 'mall_stock_array'\n"); exit(0); } }
					if(in_firm_revenues) { j = 0;
						rc = read_sales_in_mall_dynamic_array(buffer, index, &j, &current_Mall_agent->firm_revenues);
						if(rc != 0) { printf("Error: reading 'Mall' agent variable 'firm_revenues' of type 'sales_in_mall_array'\n"); exit(0); } }
					if(in_total_supply) { current_Mall_agent->total_supply = atof(buffer); }
				 }else if(in_IGFirm_agent == 1)
				{
					if(in_id) { current_IGFirm_agent->id = atoi(buffer); }
					if(in_region_id) { current_IGFirm_agent->region_id = atoi(buffer); }
					if(in_gov_id) { current_IGFirm_agent->gov_id = atoi(buffer); }
					if(in_bank_id) { current_IGFirm_agent->bank_id = atoi(buffer); }
					if(in_day_of_month_to_act) { current_IGFirm_agent->day_of_month_to_act = atoi(buffer); }
					if(in_last_day_of_month_to_act) { current_IGFirm_agent->last_day_of_month_to_act = atoi(buffer); }
					if(in_payment_account) { current_IGFirm_agent->payment_account = atof(buffer); }
					if(in_payment_account_balance_sheet) { current_IGFirm_agent->payment_account_balance_sheet = atof(buffer); }
					if(in_partition_id) { current_IGFirm_agent->partition_id = atoi(buffer); }
					if(in_init_transient_period) { current_IGFirm_agent->init_transient_period = atoi(buffer); }
					if(in_received_interest_daily) { current_IGFirm_agent->received_interest_daily = atof(buffer); }
					if(in_received_interest_in_calendar_month) { current_IGFirm_agent->received_interest_in_calendar_month = atof(buffer); }
					if(in_ebit) { current_IGFirm_agent->ebit = atof(buffer); }
					if(in_earnings) { current_IGFirm_agent->earnings = atof(buffer); }
					if(in_tax_rate_corporate) { current_IGFirm_agent->tax_rate_corporate = atof(buffer); }
					if(in_tax_rate_vat) { current_IGFirm_agent->tax_rate_vat = atof(buffer); }
					if(in_tax_payment) { current_IGFirm_agent->tax_payment = atof(buffer); }
					if(in_tax_payment_in_calendar_month) { current_IGFirm_agent->tax_payment_in_calendar_month = atof(buffer); }
					if(in_net_earnings) { current_IGFirm_agent->net_earnings = atof(buffer); }
					if(in_previous_net_earnings) { current_IGFirm_agent->previous_net_earnings = atof(buffer); }
					if(in_total_dividend_payment) { current_IGFirm_agent->total_dividend_payment = atof(buffer); }
					if(in_total_dividend_payment_in_calendar_month) { current_IGFirm_agent->total_dividend_payment_in_calendar_month = atof(buffer); }
					if(in_current_share_price) { current_IGFirm_agent->current_share_price = atof(buffer); }
					if(in_previous_dividend_per_share) { current_IGFirm_agent->previous_dividend_per_share = atof(buffer); }
					if(in_current_dividend_per_share) { current_IGFirm_agent->current_dividend_per_share = atof(buffer); }
					if(in_previous_earnings_per_share) { current_IGFirm_agent->previous_earnings_per_share = atof(buffer); }
					if(in_current_earnings_per_share) { current_IGFirm_agent->current_earnings_per_share = atof(buffer); }
					if(in_previous_dividend_per_earnings) { current_IGFirm_agent->previous_dividend_per_earnings = atof(buffer); }
					if(in_current_dividend_per_earnings) { current_IGFirm_agent->current_dividend_per_earnings = atof(buffer); }
					if(in_debt_earnings_ratio) { current_IGFirm_agent->debt_earnings_ratio = atof(buffer); }
					if(in_debt_equity_ratio) { current_IGFirm_agent->debt_equity_ratio = atof(buffer); }
					if(in_price_earnings_ratio) { current_IGFirm_agent->price_earnings_ratio = atof(buffer); }
					if(in_retained_earnings_ratio) { current_IGFirm_agent->retained_earnings_ratio = atof(buffer); }
					if(in_earnings_per_share_ratio_growth) { current_IGFirm_agent->earnings_per_share_ratio_growth = atof(buffer); }
					if(in_critical_price_earnings_ratio) { current_IGFirm_agent->critical_price_earnings_ratio = atof(buffer); }
					if(in_critical_earnings_per_share_ratio) { current_IGFirm_agent->critical_earnings_per_share_ratio = atof(buffer); }
					if(in_total_debt) { current_IGFirm_agent->total_debt = atof(buffer); }
					if(in_total_debt_balance_sheet) { current_IGFirm_agent->total_debt_balance_sheet = atof(buffer); }
					if(in_total_assets) { current_IGFirm_agent->total_assets = atof(buffer); }
					if(in_equity) { current_IGFirm_agent->equity = atof(buffer); }
					if(in_equity_balance_sheet) { current_IGFirm_agent->equity_balance_sheet = atof(buffer); }
					if(in_earnings_per_share) { current_IGFirm_agent->earnings_per_share = atof(buffer); }
					if(in_total_payments) { current_IGFirm_agent->total_payments = atof(buffer); }
					if(in_previous_shares_outstanding) { current_IGFirm_agent->previous_shares_outstanding = atoi(buffer); }
					if(in_total_income) { current_IGFirm_agent->total_income = atof(buffer); }
					if(in_total_liabilities) { current_IGFirm_agent->total_liabilities = atof(buffer); }
					if(in_total_expenses) { current_IGFirm_agent->total_expenses = atof(buffer); }
					if(in_calc_production_costs) { current_IGFirm_agent->calc_production_costs = atof(buffer); }
					if(in_productivity) { current_IGFirm_agent->productivity = atof(buffer); }
					if(in_capital_good_price) { current_IGFirm_agent->capital_good_price = atof(buffer); }
					if(in_vintages) { j = 0;
						rc = read_vintage_dynamic_array(buffer, index, &j, &current_IGFirm_agent->vintages);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'vintages' of type 'vintage_array'\n"); exit(0); } }
					if(in_sales_per_vintage) { j = 0;
						rc = read_adt_sales_per_vintage_dynamic_array(buffer, index, &j, &current_IGFirm_agent->sales_per_vintage);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'sales_per_vintage' of type 'adt_sales_per_vintage_array'\n"); exit(0); } }
					if(in_mean_productivity_of_sales) { current_IGFirm_agent->mean_productivity_of_sales = atof(buffer); }
					if(in_ratio_sold_productivity_best_practice) { current_IGFirm_agent->ratio_sold_productivity_best_practice = atof(buffer); }
					if(in_igfirm_endogenous_innovation_probability) { current_IGFirm_agent->igfirm_endogenous_innovation_probability = atof(buffer); }
					if(in_revenue_per_day) { current_IGFirm_agent->revenue_per_day = atof(buffer); }
					if(in_net_profit) { current_IGFirm_agent->net_profit = atof(buffer); }
					if(in_current_shares_outstanding) { current_IGFirm_agent->current_shares_outstanding = atoi(buffer); }
					if(in_energy_price_markup) { current_IGFirm_agent->energy_price_markup = atof(buffer); }
					if(in_energy_costs_per_day) { current_IGFirm_agent->energy_costs_per_day = atof(buffer); }
					if(in_earnings_per_day) { current_IGFirm_agent->earnings_per_day = atof(buffer); }
					if(in_cum_energy_costs) { current_IGFirm_agent->cum_energy_costs = atof(buffer); }
					if(in_last_net_profits) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_IGFirm_agent->last_net_profits);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'last_net_profits' of type 'double_array'\n"); exit(0); } }
					if(in_mean_sales_last_months) { current_IGFirm_agent->mean_sales_last_months = atof(buffer); }
					if(in_last_sales) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_IGFirm_agent->last_sales);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'last_sales' of type 'double_array'\n"); exit(0); } }
					if(in_dividend_payment) { current_IGFirm_agent->dividend_payment = atof(buffer); }
					if(in_duration_until_next_innovation) { current_IGFirm_agent->duration_until_next_innovation = atoi(buffer); }
					if(in_unit_costs) { current_IGFirm_agent->unit_costs = atof(buffer); }
					if(in_sales) { current_IGFirm_agent->sales = atof(buffer); }
					if(in_capital_good_demand) { current_IGFirm_agent->capital_good_demand = atof(buffer); }
					if(in_capital_good_demand_last_month) { current_IGFirm_agent->capital_good_demand_last_month = atof(buffer); }
					if(in_sales_last_month) { current_IGFirm_agent->sales_last_month = atof(buffer); }
					if(in_cum_revenue) { current_IGFirm_agent->cum_revenue = atof(buffer); }
					if(in_cum_revenue_last_month) { current_IGFirm_agent->cum_revenue_last_month = atof(buffer); }
					if(in_innovation_sheme_low_progress) { j = 0;
						rc = read_int_dynamic_array(buffer, index, &j, &current_IGFirm_agent->innovation_sheme_low_progress);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'innovation_sheme_low_progress' of type 'int_array'\n"); exit(0); } }
					if(in_innovation_sheme_medium_progress) { j = 0;
						rc = read_int_dynamic_array(buffer, index, &j, &current_IGFirm_agent->innovation_sheme_medium_progress);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'innovation_sheme_medium_progress' of type 'int_array'\n"); exit(0); } }
					if(in_innovation_sheme_high_progress) { j = 0;
						rc = read_int_dynamic_array(buffer, index, &j, &current_IGFirm_agent->innovation_sheme_high_progress);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'innovation_sheme_high_progress' of type 'int_array'\n"); exit(0); } }
					if(in_mean_general_skills) { current_IGFirm_agent->mean_general_skills = atof(buffer); }
					if(in_mean_adaptation_speed) { current_IGFirm_agent->mean_adaptation_speed = atof(buffer); }
					if(in_productivity_progress_in_economy) { current_IGFirm_agent->productivity_progress_in_economy = atof(buffer); }
					if(in_economy_wide_capital_stock) { current_IGFirm_agent->economy_wide_capital_stock = atof(buffer); }
					if(in_list_adaptation_speed) { j = 0;
						rc = read_adt_list_adaptation_speed_dynamic_array(buffer, index, &j, &current_IGFirm_agent->list_adaptation_speed);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'list_adaptation_speed' of type 'adt_list_adaptation_speed_array'\n"); exit(0); } }
					if(in_igfirm_balance_sheet_calendar) { j = 0;
						rc = read_igfirm_balance_sheet_adt(buffer, index, &j, &current_IGFirm_agent->igfirm_balance_sheet_calendar);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'igfirm_balance_sheet_calendar' of type 'igfirm_balance_sheet_adt'\n"); exit(0); } }
					if(in_igfirm_stocks_calendar) { j = 0;
						rc = read_igfirm_stocks_adt(buffer, index, &j, &current_IGFirm_agent->igfirm_stocks_calendar);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'igfirm_stocks_calendar' of type 'igfirm_stocks_adt'\n"); exit(0); } }
					if(in_igfirm_outflows_calendar) { j = 0;
						rc = read_igfirm_outflows_adt(buffer, index, &j, &current_IGFirm_agent->igfirm_outflows_calendar);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'igfirm_outflows_calendar' of type 'igfirm_outflows_adt'\n"); exit(0); } }
					if(in_igfirm_inflows_calendar) { j = 0;
						rc = read_igfirm_inflows_adt(buffer, index, &j, &current_IGFirm_agent->igfirm_inflows_calendar);
						if(rc != 0) { printf("Error: reading 'IGFirm' agent variable 'igfirm_inflows_calendar' of type 'igfirm_inflows_adt'\n"); exit(0); } }
					if(in_age) { current_IGFirm_agent->age = atoi(buffer); }
					if(in_transfer_payment) { current_IGFirm_agent->transfer_payment = atof(buffer); }
					if(in_subsidy_pct) { current_IGFirm_agent->subsidy_pct = atof(buffer); }
					if(in_active) { current_IGFirm_agent->active = atoi(buffer); }
					if(in_bankruptcy_idle_counter) { current_IGFirm_agent->bankruptcy_idle_counter = atoi(buffer); }
					if(in_bankruptcy_state) { current_IGFirm_agent->bankruptcy_state = atoi(buffer); }
					if(in_bankruptcy_insolvency_state) { current_IGFirm_agent->bankruptcy_insolvency_state = atoi(buffer); }
					if(in_bankruptcy_illiquidity_state) { current_IGFirm_agent->bankruptcy_illiquidity_state = atoi(buffer); }
					if(in_financial_crisis_state) { current_IGFirm_agent->financial_crisis_state = atoi(buffer); }
					if(in_economy_wide_general_skills_in_firms) { current_IGFirm_agent->economy_wide_general_skills_in_firms = atof(buffer); }
					if(in_economy_wide_specific_skills_in_firms) { current_IGFirm_agent->economy_wide_specific_skills_in_firms = atof(buffer); }
					if(in_subsidy_payment) { current_IGFirm_agent->subsidy_payment = atof(buffer); }
					if(in_wage_offer) { current_IGFirm_agent->wage_offer = atof(buffer); }
				 }else if(in_Eurostat_agent == 1)
				{
					if(in_id) { current_Eurostat_agent->id = atoi(buffer); }
					if(in_region_id) { current_Eurostat_agent->region_id = atoi(buffer); }
					if(in_partition_id) { current_Eurostat_agent->partition_id = atoi(buffer); }
					if(in_init_transient_period) { current_Eurostat_agent->init_transient_period = atoi(buffer); }
					if(in_switch_datastorage) { current_Eurostat_agent->switch_datastorage = atoi(buffer); }
					if(in_num_households) { current_Eurostat_agent->num_households = atoi(buffer); }
					if(in_no_households_skill_1) { current_Eurostat_agent->no_households_skill_1 = atoi(buffer); }
					if(in_no_households_skill_2) { current_Eurostat_agent->no_households_skill_2 = atoi(buffer); }
					if(in_no_households_skill_3) { current_Eurostat_agent->no_households_skill_3 = atoi(buffer); }
					if(in_no_households_skill_4) { current_Eurostat_agent->no_households_skill_4 = atoi(buffer); }
					if(in_no_households_skill_5) { current_Eurostat_agent->no_households_skill_5 = atoi(buffer); }
					if(in_employed) { current_Eurostat_agent->employed = atoi(buffer); }
					if(in_employed_skill_1) { current_Eurostat_agent->employed_skill_1 = atoi(buffer); }
					if(in_employed_skill_2) { current_Eurostat_agent->employed_skill_2 = atoi(buffer); }
					if(in_employed_skill_3) { current_Eurostat_agent->employed_skill_3 = atoi(buffer); }
					if(in_employed_skill_4) { current_Eurostat_agent->employed_skill_4 = atoi(buffer); }
					if(in_employed_skill_5) { current_Eurostat_agent->employed_skill_5 = atoi(buffer); }
					if(in_unemployed) { current_Eurostat_agent->unemployed = atoi(buffer); }
					if(in_unemployment_rate) { current_Eurostat_agent->unemployment_rate = atof(buffer); }
					if(in_employment_rate) { current_Eurostat_agent->employment_rate = atof(buffer); }
					if(in_unemployment_rate_skill_1) { current_Eurostat_agent->unemployment_rate_skill_1 = atof(buffer); }
					if(in_unemployment_rate_skill_2) { current_Eurostat_agent->unemployment_rate_skill_2 = atof(buffer); }
					if(in_unemployment_rate_skill_3) { current_Eurostat_agent->unemployment_rate_skill_3 = atof(buffer); }
					if(in_unemployment_rate_skill_4) { current_Eurostat_agent->unemployment_rate_skill_4 = atof(buffer); }
					if(in_unemployment_rate_skill_5) { current_Eurostat_agent->unemployment_rate_skill_5 = atof(buffer); }
					if(in_average_wage) { current_Eurostat_agent->average_wage = atof(buffer); }
					if(in_average_wage_skill_1) { current_Eurostat_agent->average_wage_skill_1 = atof(buffer); }
					if(in_average_wage_skill_2) { current_Eurostat_agent->average_wage_skill_2 = atof(buffer); }
					if(in_average_wage_skill_3) { current_Eurostat_agent->average_wage_skill_3 = atof(buffer); }
					if(in_average_wage_skill_4) { current_Eurostat_agent->average_wage_skill_4 = atof(buffer); }
					if(in_average_wage_skill_5) { current_Eurostat_agent->average_wage_skill_5 = atof(buffer); }
					if(in_average_s_skill) { current_Eurostat_agent->average_s_skill = atof(buffer); }
					if(in_average_s_skill_1) { current_Eurostat_agent->average_s_skill_1 = atof(buffer); }
					if(in_average_s_skill_2) { current_Eurostat_agent->average_s_skill_2 = atof(buffer); }
					if(in_average_s_skill_3) { current_Eurostat_agent->average_s_skill_3 = atof(buffer); }
					if(in_average_s_skill_4) { current_Eurostat_agent->average_s_skill_4 = atof(buffer); }
					if(in_average_s_skill_5) { current_Eurostat_agent->average_s_skill_5 = atof(buffer); }
					if(in_total_consumption_budget) { current_Eurostat_agent->total_consumption_budget = atof(buffer); }
					if(in_no_firms) { current_Eurostat_agent->no_firms = atoi(buffer); }
					if(in_no_active_firms) { current_Eurostat_agent->no_active_firms = atoi(buffer); }
					if(in_no_vacancies) { current_Eurostat_agent->no_vacancies = atoi(buffer); }
					if(in_no_posted_vacancies) { current_Eurostat_agent->no_posted_vacancies = atoi(buffer); }
					if(in_no_employees) { current_Eurostat_agent->no_employees = atoi(buffer); }
					if(in_no_employees_production) { current_Eurostat_agent->no_employees_production = atoi(buffer); }
					if(in_no_employees_r_and_d) { current_Eurostat_agent->no_employees_r_and_d = atoi(buffer); }
					if(in_no_employees_skill_1) { current_Eurostat_agent->no_employees_skill_1 = atoi(buffer); }
					if(in_no_employees_skill_2) { current_Eurostat_agent->no_employees_skill_2 = atoi(buffer); }
					if(in_no_employees_skill_3) { current_Eurostat_agent->no_employees_skill_3 = atoi(buffer); }
					if(in_no_employees_skill_4) { current_Eurostat_agent->no_employees_skill_4 = atoi(buffer); }
					if(in_no_employees_skill_5) { current_Eurostat_agent->no_employees_skill_5 = atoi(buffer); }
					if(in_firm_average_wage) { current_Eurostat_agent->firm_average_wage = atof(buffer); }
					if(in_firm_average_production_wage) { current_Eurostat_agent->firm_average_production_wage = atof(buffer); }
					if(in_firm_average_r_and_d_wage) { current_Eurostat_agent->firm_average_r_and_d_wage = atof(buffer); }
					if(in_firm_average_wage_skill_1) { current_Eurostat_agent->firm_average_wage_skill_1 = atof(buffer); }
					if(in_firm_average_wage_skill_2) { current_Eurostat_agent->firm_average_wage_skill_2 = atof(buffer); }
					if(in_firm_average_wage_skill_3) { current_Eurostat_agent->firm_average_wage_skill_3 = atof(buffer); }
					if(in_firm_average_wage_skill_4) { current_Eurostat_agent->firm_average_wage_skill_4 = atof(buffer); }
					if(in_firm_average_wage_skill_5) { current_Eurostat_agent->firm_average_wage_skill_5 = atof(buffer); }
					if(in_firm_average_g_skill) { current_Eurostat_agent->firm_average_g_skill = atof(buffer); }
					if(in_firm_average_s_skill) { current_Eurostat_agent->firm_average_s_skill = atof(buffer); }
					if(in_firm_average_s_skill_1) { current_Eurostat_agent->firm_average_s_skill_1 = atof(buffer); }
					if(in_firm_average_s_skill_2) { current_Eurostat_agent->firm_average_s_skill_2 = atof(buffer); }
					if(in_firm_average_s_skill_3) { current_Eurostat_agent->firm_average_s_skill_3 = atof(buffer); }
					if(in_firm_average_s_skill_4) { current_Eurostat_agent->firm_average_s_skill_4 = atof(buffer); }
					if(in_firm_average_s_skill_5) { current_Eurostat_agent->firm_average_s_skill_5 = atof(buffer); }
					if(in_firm_average_quality) { current_Eurostat_agent->firm_average_quality = atof(buffer); }
					if(in_firm_average_price) { current_Eurostat_agent->firm_average_price = atof(buffer); }
					if(in_region_firm_data) { j = 0;
						rc = read_firm_data_dynamic_array(buffer, index, &j, &current_Eurostat_agent->region_firm_data);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'region_firm_data' of type 'firm_data_array'\n"); exit(0); } }
					if(in_region_household_data) { j = 0;
						rc = read_household_data_dynamic_array(buffer, index, &j, &current_Eurostat_agent->region_household_data);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'region_household_data' of type 'household_data_array'\n"); exit(0); } }
					if(in_total_earnings) { current_Eurostat_agent->total_earnings = atof(buffer); }
					if(in_total_debt) { current_Eurostat_agent->total_debt = atof(buffer); }
					if(in_total_assets) { current_Eurostat_agent->total_assets = atof(buffer); }
					if(in_total_equity) { current_Eurostat_agent->total_equity = atof(buffer); }
					if(in_average_debt_earnings_ratio) { current_Eurostat_agent->average_debt_earnings_ratio = atof(buffer); }
					if(in_average_debt_equity_ratio) { current_Eurostat_agent->average_debt_equity_ratio = atof(buffer); }
					if(in_labour_share_ratio) { current_Eurostat_agent->labour_share_ratio = atof(buffer); }
					if(in_cpi) { current_Eurostat_agent->cpi = atof(buffer); }
					if(in_hpi) { current_Eurostat_agent->hpi = atof(buffer); }
					if(in_hmr_price_index) { j = 0;
						rc = read_price_index_adt(buffer, index, &j, &current_Eurostat_agent->hmr_price_index);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'hmr_price_index' of type 'price_index_adt'\n"); exit(0); } }
					if(in_hmr_price_data) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Eurostat_agent->hmr_price_data);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'hmr_price_data' of type 'double_array'\n"); exit(0); } }
					if(in_op_price_index) { j = 0;
						rc = read_price_index_adt(buffer, index, &j, &current_Eurostat_agent->op_price_index);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'op_price_index' of type 'price_index_adt'\n"); exit(0); } }
					if(in_op_price_data) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Eurostat_agent->op_price_data);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'op_price_data' of type 'double_array'\n"); exit(0); } }
					if(in_rent_price_index) { j = 0;
						rc = read_price_index_adt(buffer, index, &j, &current_Eurostat_agent->rent_price_index);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'rent_price_index' of type 'price_index_adt'\n"); exit(0); } }
					if(in_rent_price_data) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Eurostat_agent->rent_price_data);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'rent_price_data' of type 'double_array'\n"); exit(0); } }
					if(in_hmr_price_mean) { current_Eurostat_agent->hmr_price_mean = atof(buffer); }
					if(in_op_price_mean) { current_Eurostat_agent->op_price_mean = atof(buffer); }
					if(in_rent_price_mean) { current_Eurostat_agent->rent_price_mean = atof(buffer); }
					if(in_count_tenants) { current_Eurostat_agent->count_tenants = atoi(buffer); }
					if(in_count_owners) { current_Eurostat_agent->count_owners = atoi(buffer); }
					if(in_count_landlords) { current_Eurostat_agent->count_landlords = atoi(buffer); }
					if(in_gdp) { current_Eurostat_agent->gdp = atof(buffer); }
					if(in_monthly_investment_value) { current_Eurostat_agent->monthly_investment_value = atof(buffer); }
					if(in_monthly_sold_quantity) { current_Eurostat_agent->monthly_sold_quantity = atof(buffer); }
					if(in_herfindahl_index) { current_Eurostat_agent->herfindahl_index = atof(buffer); }
					if(in_monthly_output) { current_Eurostat_agent->monthly_output = atof(buffer); }
					if(in_monthly_revenue) { current_Eurostat_agent->monthly_revenue = atof(buffer); }
					if(in_monthly_planned_output) { current_Eurostat_agent->monthly_planned_output = atof(buffer); }
					if(in_price_index) { current_Eurostat_agent->price_index = atof(buffer); }
					if(in_history_monthly) { j = 0;
						rc = read_history_item_static_array(buffer, index, &j, current_Eurostat_agent->history_monthly, 13);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'history_monthly' of type 'history_item'\n"); exit(0); } }
					if(in_history_quarterly) { j = 0;
						rc = read_history_item_static_array(buffer, index, &j, current_Eurostat_agent->history_quarterly, 5);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'history_quarterly' of type 'history_item'\n"); exit(0); } }
					if(in_monthly_growth_rates) { j = 0;
						rc = read_history_item(buffer, index, &j, &current_Eurostat_agent->monthly_growth_rates);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'monthly_growth_rates' of type 'history_item'\n"); exit(0); } }
					if(in_quarterly_growth_rates) { j = 0;
						rc = read_history_item(buffer, index, &j, &current_Eurostat_agent->quarterly_growth_rates);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'quarterly_growth_rates' of type 'history_item'\n"); exit(0); } }
					if(in_annual_growth_rates_monthly) { j = 0;
						rc = read_history_item(buffer, index, &j, &current_Eurostat_agent->annual_growth_rates_monthly);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'annual_growth_rates_monthly' of type 'history_item'\n"); exit(0); } }
					if(in_annual_growth_rates_quarterly) { j = 0;
						rc = read_history_item(buffer, index, &j, &current_Eurostat_agent->annual_growth_rates_quarterly);
						if(rc != 0) { printf("Error: reading 'Eurostat' agent variable 'annual_growth_rates_quarterly' of type 'history_item'\n"); exit(0); } }
					if(in_no_firm_births) { current_Eurostat_agent->no_firm_births = atoi(buffer); }
					if(in_no_firm_deaths) { current_Eurostat_agent->no_firm_deaths = atoi(buffer); }
					if(in_firm_birth_rate) { current_Eurostat_agent->firm_birth_rate = atof(buffer); }
					if(in_firm_death_rate) { current_Eurostat_agent->firm_death_rate = atof(buffer); }
					if(in_max_firm_creation) { current_Eurostat_agent->max_firm_creation = atoi(buffer); }
					if(in_recession_started) { current_Eurostat_agent->recession_started = atoi(buffer); }
					if(in_recession_duration) { current_Eurostat_agent->recession_duration = atoi(buffer); }
					if(in_firm_average_productivity_progress) { current_Eurostat_agent->firm_average_productivity_progress = atof(buffer); }
					if(in_firm_average_productivity) { current_Eurostat_agent->firm_average_productivity = atof(buffer); }
					if(in_investment_gdp_ratio) { current_Eurostat_agent->investment_gdp_ratio = atof(buffer); }
					if(in_total_capital_stock_units) { current_Eurostat_agent->total_capital_stock_units = atof(buffer); }
					if(in_total_value_mall_inventories) { current_Eurostat_agent->total_value_mall_inventories = atof(buffer); }
					if(in_total_dividends) { current_Eurostat_agent->total_dividends = atof(buffer); }
					if(in_base_wage_offer) { current_Eurostat_agent->base_wage_offer = atof(buffer); }
					if(in_just_employed) { current_Eurostat_agent->just_employed = atoi(buffer); }
					if(in_just_unemployed) { current_Eurostat_agent->just_unemployed = atoi(buffer); }
					if(in_start_employed) { current_Eurostat_agent->start_employed = atoi(buffer); }
					if(in_start_unemployed) { current_Eurostat_agent->start_unemployed = atoi(buffer); }
					if(in_enter_matching) { current_Eurostat_agent->enter_matching = atoi(buffer); }
					if(in_unemployed_duration) { current_Eurostat_agent->unemployed_duration = atoi(buffer); }
					if(in_job_seperation_rate) { current_Eurostat_agent->job_seperation_rate = atof(buffer); }
					if(in_job_finding_rate) { current_Eurostat_agent->job_finding_rate = atof(buffer); }
					if(in_v_u_ratio) { current_Eurostat_agent->v_u_ratio = atof(buffer); }
					if(in_matching_rate) { current_Eurostat_agent->matching_rate = atof(buffer); }
					if(in_hh_payment_account) { current_Eurostat_agent->hh_payment_account = atof(buffer); }
					if(in_mean_net_income) { current_Eurostat_agent->mean_net_income = atof(buffer); }
				 }else if(in_Bank_agent == 1)
				{
					if(in_id) { current_Bank_agent->id = atoi(buffer); }
					if(in_region_id) { current_Bank_agent->region_id = atoi(buffer); }
					if(in_gov_id) { current_Bank_agent->gov_id = atoi(buffer); }
					if(in_partition_id) { current_Bank_agent->partition_id = atoi(buffer); }
					if(in_init_transient_period) { current_Bank_agent->init_transient_period = atoi(buffer); }
					if(in_plan_sell_house) { current_Bank_agent->plan_sell_house = atoi(buffer); }
					if(in_lookuptable_riskweights_mortgages) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->lookuptable_riskweights_mortgages);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'lookuptable_riskweights_mortgages' of type 'double_array'\n"); exit(0); } }
					if(in_basel_risk_weight) { current_Bank_agent->basel_risk_weight = atof(buffer); }
					if(in_firm_npl_daily) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->firm_npl_daily);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'firm_npl_daily' of type 'double_array'\n"); exit(0); } }
					if(in_firm_ld_daily) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->firm_ld_daily);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'firm_ld_daily' of type 'double_array'\n"); exit(0); } }
					if(in_firm_ll_daily) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->firm_ll_daily);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'firm_ll_daily' of type 'double_array'\n"); exit(0); } }
					if(in_firm_pl_daily) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->firm_pl_daily);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'firm_pl_daily' of type 'double_array'\n"); exit(0); } }
					if(in_firm_pd_qtr) { current_Bank_agent->firm_pd_qtr = atof(buffer); }
					if(in_firm_pd_year) { current_Bank_agent->firm_pd_year = atof(buffer); }
					if(in_firm_lgd_qtr) { current_Bank_agent->firm_lgd_qtr = atof(buffer); }
					if(in_firm_lgd_year) { current_Bank_agent->firm_lgd_year = atof(buffer); }
					if(in_firm_el_qtr) { current_Bank_agent->firm_el_qtr = atof(buffer); }
					if(in_firm_pd_cycle) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->firm_pd_cycle);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'firm_pd_cycle' of type 'double_array'\n"); exit(0); } }
					if(in_firm_lgd_cycle) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->firm_lgd_cycle);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'firm_lgd_cycle' of type 'double_array'\n"); exit(0); } }
					if(in_firm_pd_ttc) { current_Bank_agent->firm_pd_ttc = atof(buffer); }
					if(in_firm_lgd_ttc) { current_Bank_agent->firm_lgd_ttc = atof(buffer); }
					if(in_hh_npl_daily) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->hh_npl_daily);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'hh_npl_daily' of type 'double_array'\n"); exit(0); } }
					if(in_hh_ll_daily) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->hh_ll_daily);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'hh_ll_daily' of type 'double_array'\n"); exit(0); } }
					if(in_hh_ld_daily) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->hh_ld_daily);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'hh_ld_daily' of type 'double_array'\n"); exit(0); } }
					if(in_hh_pl_daily) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->hh_pl_daily);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'hh_pl_daily' of type 'double_array'\n"); exit(0); } }
					if(in_hh_pd_qtr) { current_Bank_agent->hh_pd_qtr = atof(buffer); }
					if(in_hh_pd_year) { current_Bank_agent->hh_pd_year = atof(buffer); }
					if(in_hh_lgd_qtr) { current_Bank_agent->hh_lgd_qtr = atof(buffer); }
					if(in_hh_lgd_year) { current_Bank_agent->hh_lgd_year = atof(buffer); }
					if(in_hh_el_qtr) { current_Bank_agent->hh_el_qtr = atof(buffer); }
					if(in_hh_pd_cycle) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->hh_pd_cycle);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'hh_pd_cycle' of type 'double_array'\n"); exit(0); } }
					if(in_hh_lgd_cycle) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->hh_lgd_cycle);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'hh_lgd_cycle' of type 'double_array'\n"); exit(0); } }
					if(in_hh_pd_ttc) { current_Bank_agent->hh_pd_ttc = atof(buffer); }
					if(in_hh_lgd_ttc) { current_Bank_agent->hh_lgd_ttc = atof(buffer); }
					if(in_active) { current_Bank_agent->active = atoi(buffer); }
					if(in_inactive) { current_Bank_agent->inactive = atoi(buffer); }
					if(in_cash) { current_Bank_agent->cash = atof(buffer); }
					if(in_reserves) { current_Bank_agent->reserves = atof(buffer); }
					if(in_regulatory_reserves) { current_Bank_agent->regulatory_reserves = atof(buffer); }
					if(in_total_credit) { current_Bank_agent->total_credit = atof(buffer); }
					if(in_equity) { current_Bank_agent->equity = atof(buffer); }
					if(in_ecb_debt) { current_Bank_agent->ecb_debt = atof(buffer); }
					if(in_risk_exposure) { current_Bank_agent->risk_exposure = atof(buffer); }
					if(in_deposit_interest_rate) { current_Bank_agent->deposit_interest_rate = atof(buffer); }
					if(in_bank_gamma) { j = 0;
						rc = read_double_static_array(buffer, index, &j, current_Bank_agent->bank_gamma, 2);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'bank_gamma' of type 'double'\n"); exit(0); } }
					if(in_profits) { j = 0;
						rc = read_double_static_array(buffer, index, &j, current_Bank_agent->profits, 2);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'profits' of type 'double'\n"); exit(0); } }
					if(in_bank_dividend_rate) { current_Bank_agent->bank_dividend_rate = atof(buffer); }
					if(in_tax_rate_corporate) { current_Bank_agent->tax_rate_corporate = atof(buffer); }
					if(in_current_shares_outstanding) { current_Bank_agent->current_shares_outstanding = atoi(buffer); }
					if(in_debt_period) { current_Bank_agent->debt_period = atof(buffer); }
					if(in_loan_request_message_found) { current_Bank_agent->loan_request_message_found = atoi(buffer); }
					if(in_day_of_month_to_act) { current_Bank_agent->day_of_month_to_act = atoi(buffer); }
					if(in_deposits) { current_Bank_agent->deposits = atof(buffer); }
					if(in_deposits_previous) { current_Bank_agent->deposits_previous = atof(buffer); }
					if(in_firm_loan_installments) { current_Bank_agent->firm_loan_installments = atof(buffer); }
					if(in_firm_loan_installments_in_calendar_month) { current_Bank_agent->firm_loan_installments_in_calendar_month = atof(buffer); }
					if(in_firm_interest_payments) { current_Bank_agent->firm_interest_payments = atof(buffer); }
					if(in_firm_interest_payments_in_calendar_month) { current_Bank_agent->firm_interest_payments_in_calendar_month = atof(buffer); }
					if(in_firm_loan_issues) { current_Bank_agent->firm_loan_issues = atof(buffer); }
					if(in_ecb_interest_payment) { current_Bank_agent->ecb_interest_payment = atof(buffer); }
					if(in_total_dividend_payment) { current_Bank_agent->total_dividend_payment = atof(buffer); }
					if(in_total_dividends_in_calendar_month) { current_Bank_agent->total_dividends_in_calendar_month = atof(buffer); }
					if(in_taxes) { current_Bank_agent->taxes = atof(buffer); }
					if(in_dividend_per_share) { current_Bank_agent->dividend_per_share = atof(buffer); }
					if(in_current_share_price) { current_Bank_agent->current_share_price = atof(buffer); }
					if(in_leverage_ratio) { current_Bank_agent->leverage_ratio = atof(buffer); }
					if(in_reserve_deposit_ratio) { current_Bank_agent->reserve_deposit_ratio = atof(buffer); }
					if(in_equity_asset_ratio) { current_Bank_agent->equity_asset_ratio = atof(buffer); }
					if(in_debt_equity_ratio) { current_Bank_agent->debt_equity_ratio = atof(buffer); }
					if(in_mean_interest_rate) { current_Bank_agent->mean_interest_rate = atof(buffer); }
					if(in_sum_new_interest_rates_in_calendar_month) { current_Bank_agent->sum_new_interest_rates_in_calendar_month = atof(buffer); }
					if(in_no_new_loans_in_calendar_month) { current_Bank_agent->no_new_loans_in_calendar_month = atoi(buffer); }
					if(in_paid_interest_daily) { current_Bank_agent->paid_interest_daily = atof(buffer); }
					if(in_paid_interest_in_calendar_month) { current_Bank_agent->paid_interest_in_calendar_month = atof(buffer); }
					if(in_excess_risk_exposure) { current_Bank_agent->excess_risk_exposure = atof(buffer); }
					if(in_excess_liquidity) { current_Bank_agent->excess_liquidity = atof(buffer); }
					if(in_total_bad_debt_calendar_month) { current_Bank_agent->total_bad_debt_calendar_month = atof(buffer); }
					if(in_proba_default_distribution) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_Bank_agent->proba_default_distribution);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'proba_default_distribution' of type 'double_array'\n"); exit(0); } }
					if(in_liquidity_coverage_ratio) { current_Bank_agent->liquidity_coverage_ratio = atof(buffer); }
					if(in_bank_balance_sheet_calendar) { j = 0;
						rc = read_bank_balance_sheet_adt(buffer, index, &j, &current_Bank_agent->bank_balance_sheet_calendar);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'bank_balance_sheet_calendar' of type 'bank_balance_sheet_adt'\n"); exit(0); } }
					if(in_bank_stocks_calendar) { j = 0;
						rc = read_bank_stocks_adt(buffer, index, &j, &current_Bank_agent->bank_stocks_calendar);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'bank_stocks_calendar' of type 'bank_stocks_adt'\n"); exit(0); } }
					if(in_bank_outflows_calendar) { j = 0;
						rc = read_bank_outflows_adt(buffer, index, &j, &current_Bank_agent->bank_outflows_calendar);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'bank_outflows_calendar' of type 'bank_outflows_adt'\n"); exit(0); } }
					if(in_bank_inflows_calendar) { j = 0;
						rc = read_bank_inflows_adt(buffer, index, &j, &current_Bank_agent->bank_inflows_calendar);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'bank_inflows_calendar' of type 'bank_inflows_adt'\n"); exit(0); } }
					if(in_total_income) { current_Bank_agent->total_income = atof(buffer); }
					if(in_total_expenses) { current_Bank_agent->total_expenses = atof(buffer); }
					if(in_total_assets) { current_Bank_agent->total_assets = atof(buffer); }
					if(in_total_liabilities) { current_Bank_agent->total_liabilities = atof(buffer); }
					if(in_loan_loss_reserve_firm_loans) { current_Bank_agent->loan_loss_reserve_firm_loans = atof(buffer); }
					if(in_loan_loss_reserve_mortgage_loans) { current_Bank_agent->loan_loss_reserve_mortgage_loans = atof(buffer); }
					if(in_mortgage_portfolio) { j = 0;
						rc = read_mortgage_contract_adt_dynamic_array(buffer, index, &j, &current_Bank_agent->mortgage_portfolio);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'mortgage_portfolio' of type 'mortgage_contract_adt_array'\n"); exit(0); } }
					if(in_bank_inflows_monthly_mortgage_payments) { current_Bank_agent->bank_inflows_monthly_mortgage_payments = atof(buffer); }
					if(in_bank_outflows_monthly_mortgage_issues) { current_Bank_agent->bank_outflows_monthly_mortgage_issues = atof(buffer); }
					if(in_no_monthly_new_mortgages_flow) { current_Bank_agent->no_monthly_new_mortgages_flow = atoi(buffer); }
					if(in_no_mortgages_outstanding) { current_Bank_agent->no_mortgages_outstanding = atoi(buffer); }
					if(in_seized_collateral) { j = 0;
						rc = read_foreclosure_adt_dynamic_array(buffer, index, &j, &current_Bank_agent->seized_collateral);
						if(rc != 0) { printf("Error: reading 'Bank' agent variable 'seized_collateral' of type 'foreclosure_adt_array'\n"); exit(0); } }
				 }else if(in_Government_agent == 1)
				{
					if(in_id) { current_Government_agent->id = atoi(buffer); }
					if(in_list_of_regions) { j = 0;
						rc = read_int_dynamic_array(buffer, index, &j, &current_Government_agent->list_of_regions);
						if(rc != 0) { printf("Error: reading 'Government' agent variable 'list_of_regions' of type 'int_array'\n"); exit(0); } }
					if(in_payment_account) { current_Government_agent->payment_account = atof(buffer); }
					if(in_day_of_month_to_act) { current_Government_agent->day_of_month_to_act = atoi(buffer); }
					if(in_region_id) { current_Government_agent->region_id = atoi(buffer); }
					if(in_partition_id) { current_Government_agent->partition_id = atoi(buffer); }
					if(in_init_transient_period) { current_Government_agent->init_transient_period = atoi(buffer); }
					if(in_unemployment_benefit_pct) { current_Government_agent->unemployment_benefit_pct = atof(buffer); }
					if(in_gdp_fraction_consumption) { current_Government_agent->gdp_fraction_consumption = atof(buffer); }
					if(in_gdp_fraction_investment) { current_Government_agent->gdp_fraction_investment = atof(buffer); }
					if(in_tax_rate_corporate) { current_Government_agent->tax_rate_corporate = atof(buffer); }
					if(in_tax_rate_hh_labour) { current_Government_agent->tax_rate_hh_labour = atof(buffer); }
					if(in_tax_rate_hh_capital) { current_Government_agent->tax_rate_hh_capital = atof(buffer); }
					if(in_tax_rate_vat) { current_Government_agent->tax_rate_vat = atof(buffer); }
					if(in_monthly_tax_revenues) { current_Government_agent->monthly_tax_revenues = atof(buffer); }
					if(in_yearly_tax_revenues) { current_Government_agent->yearly_tax_revenues = atof(buffer); }
					if(in_monthly_benefit_payment) { current_Government_agent->monthly_benefit_payment = atof(buffer); }
					if(in_yearly_benefit_payment) { current_Government_agent->yearly_benefit_payment = atof(buffer); }
					if(in_hh_transfer_payment) { current_Government_agent->hh_transfer_payment = atof(buffer); }
					if(in_firm_transfer_payment) { current_Government_agent->firm_transfer_payment = atof(buffer); }
					if(in_monthly_transfer_payment) { current_Government_agent->monthly_transfer_payment = atof(buffer); }
					if(in_yearly_transfer_payment) { current_Government_agent->yearly_transfer_payment = atof(buffer); }
					if(in_hh_subsidy_pct) { current_Government_agent->hh_subsidy_pct = atof(buffer); }
					if(in_firm_subsidy_pct) { current_Government_agent->firm_subsidy_pct = atof(buffer); }
					if(in_regional_firm_subsidy) { current_Government_agent->regional_firm_subsidy = atoi(buffer); }
					if(in_subsidy_flag) { current_Government_agent->subsidy_flag = atoi(buffer); }
					if(in_gov_interest_rate) { current_Government_agent->gov_interest_rate = atof(buffer); }
					if(in_monthly_bond_interest_payment) { current_Government_agent->monthly_bond_interest_payment = atof(buffer); }
					if(in_monthly_subsidy_payment) { current_Government_agent->monthly_subsidy_payment = atof(buffer); }
					if(in_monthly_consumption_expenditure) { current_Government_agent->monthly_consumption_expenditure = atof(buffer); }
					if(in_monthly_investment_expenditure) { current_Government_agent->monthly_investment_expenditure = atof(buffer); }
					if(in_monthly_budget_balance) { current_Government_agent->monthly_budget_balance = atof(buffer); }
					if(in_monthly_gdp) { current_Government_agent->monthly_gdp = atof(buffer); }
					if(in_monthly_budget_balance_gdp_fraction) { current_Government_agent->monthly_budget_balance_gdp_fraction = atof(buffer); }
					if(in_monthly_consumption_budget) { current_Government_agent->monthly_consumption_budget = atof(buffer); }
					if(in_monthly_investment_budget) { current_Government_agent->monthly_investment_budget = atof(buffer); }
					if(in_monthly_income) { current_Government_agent->monthly_income = atof(buffer); }
					if(in_monthly_expenditure) { current_Government_agent->monthly_expenditure = atof(buffer); }
					if(in_yearly_subsidy_payment) { current_Government_agent->yearly_subsidy_payment = atof(buffer); }
					if(in_yearly_bond_interest_payment) { current_Government_agent->yearly_bond_interest_payment = atof(buffer); }
					if(in_yearly_investment_expenditure) { current_Government_agent->yearly_investment_expenditure = atof(buffer); }
					if(in_yearly_consumption_expenditure) { current_Government_agent->yearly_consumption_expenditure = atof(buffer); }
					if(in_yearly_income) { current_Government_agent->yearly_income = atof(buffer); }
					if(in_yearly_expenditure) { current_Government_agent->yearly_expenditure = atof(buffer); }
					if(in_total_debt) { current_Government_agent->total_debt = atof(buffer); }
					if(in_yearly_budget_balance) { current_Government_agent->yearly_budget_balance = atof(buffer); }
					if(in_total_money_financing) { current_Government_agent->total_money_financing = atof(buffer); }
					if(in_total_bond_financing) { current_Government_agent->total_bond_financing = atof(buffer); }
					if(in_country_wide_mean_wage) { current_Government_agent->country_wide_mean_wage = atof(buffer); }
					if(in_num_unemployed) { current_Government_agent->num_unemployed = atoi(buffer); }
					if(in_yearly_gdp) { current_Government_agent->yearly_gdp = atof(buffer); }
					if(in_previous_year_gdp) { current_Government_agent->previous_year_gdp = atof(buffer); }
					if(in_gdp_growth) { current_Government_agent->gdp_growth = atof(buffer); }
					if(in_gdp_forecast) { current_Government_agent->gdp_forecast = atof(buffer); }
					if(in_yearly_income_forecast) { current_Government_agent->yearly_income_forecast = atof(buffer); }
					if(in_yearly_expenditure_budget) { current_Government_agent->yearly_expenditure_budget = atof(buffer); }
					if(in_budget_balance_forecast) { current_Government_agent->budget_balance_forecast = atof(buffer); }
					if(in_yearly_consumption_budget) { current_Government_agent->yearly_consumption_budget = atof(buffer); }
					if(in_yearly_investment_budget) { current_Government_agent->yearly_investment_budget = atof(buffer); }
					if(in_yearly_budget_balance_gdp_fraction) { current_Government_agent->yearly_budget_balance_gdp_fraction = atof(buffer); }
					if(in_total_assets) { current_Government_agent->total_assets = atof(buffer); }
					if(in_total_liabilities) { current_Government_agent->total_liabilities = atof(buffer); }
					if(in_cumulated_deficit) { current_Government_agent->cumulated_deficit = atof(buffer); }
					if(in_inflation_rate) { current_Government_agent->inflation_rate = atof(buffer); }
					if(in_unemployment_rate) { current_Government_agent->unemployment_rate = atof(buffer); }
					if(in_human_capital_policy_installation_date_in_years) { current_Government_agent->human_capital_policy_installation_date_in_years = atoi(buffer); }
					if(in_human_capital_policy_flag) { current_Government_agent->human_capital_policy_flag = atoi(buffer); }
					if(in_new_skill_distribution) { j = 0;
						rc = read_adt_skill_distribution_dynamic_array(buffer, index, &j, &current_Government_agent->new_skill_distribution);
						if(rc != 0) { printf("Error: reading 'Government' agent variable 'new_skill_distribution' of type 'adt_skill_distribution_array'\n"); exit(0); } }
					if(in_gov_balance_sheet_calendar) { j = 0;
						rc = read_gov_balance_sheet_adt(buffer, index, &j, &current_Government_agent->gov_balance_sheet_calendar);
						if(rc != 0) { printf("Error: reading 'Government' agent variable 'gov_balance_sheet_calendar' of type 'gov_balance_sheet_adt'\n"); exit(0); } }
					if(in_gov_stocks_calendar) { j = 0;
						rc = read_gov_stocks_adt(buffer, index, &j, &current_Government_agent->gov_stocks_calendar);
						if(rc != 0) { printf("Error: reading 'Government' agent variable 'gov_stocks_calendar' of type 'gov_stocks_adt'\n"); exit(0); } }
					if(in_gov_outflows_calendar) { j = 0;
						rc = read_gov_outflows_adt(buffer, index, &j, &current_Government_agent->gov_outflows_calendar);
						if(rc != 0) { printf("Error: reading 'Government' agent variable 'gov_outflows_calendar' of type 'gov_outflows_adt'\n"); exit(0); } }
					if(in_gov_inflows_calendar) { j = 0;
						rc = read_gov_inflows_adt(buffer, index, &j, &current_Government_agent->gov_inflows_calendar);
						if(rc != 0) { printf("Error: reading 'Government' agent variable 'gov_inflows_calendar' of type 'gov_inflows_adt'\n"); exit(0); } }
				 }else if(in_CentralBank_agent == 1)
				{
					if(in_id) { current_CentralBank_agent->id = atoi(buffer); }
					if(in_region_id) { current_CentralBank_agent->region_id = atoi(buffer); }
					if(in_partition_id) { current_CentralBank_agent->partition_id = atoi(buffer); }
					if(in_init_transient_period) { current_CentralBank_agent->init_transient_period = atoi(buffer); }
					if(in_equity) { current_CentralBank_agent->equity = atof(buffer); }
					if(in_dividend_payment) { current_CentralBank_agent->dividend_payment = atof(buffer); }
					if(in_fiat_money) { current_CentralBank_agent->fiat_money = atof(buffer); }
					if(in_fiat_money_banks) { current_CentralBank_agent->fiat_money_banks = atof(buffer); }
					if(in_fiat_money_firms) { current_CentralBank_agent->fiat_money_firms = atof(buffer); }
					if(in_ecb_deposits) { current_CentralBank_agent->ecb_deposits = atof(buffer); }
					if(in_accounts_banks) { j = 0;
						rc = read_account_item_dynamic_array(buffer, index, &j, &current_CentralBank_agent->accounts_banks);
						if(rc != 0) { printf("Error: reading 'CentralBank' agent variable 'accounts_banks' of type 'account_item_array'\n"); exit(0); } }
					if(in_accounts_govs) { j = 0;
						rc = read_account_item_dynamic_array(buffer, index, &j, &current_CentralBank_agent->accounts_govs);
						if(rc != 0) { printf("Error: reading 'CentralBank' agent variable 'accounts_govs' of type 'account_item_array'\n"); exit(0); } }
					if(in_cash) { current_CentralBank_agent->cash = atof(buffer); }
					if(in_ecb_balance_sheet_calendar) { j = 0;
						rc = read_ecb_balance_sheet_adt(buffer, index, &j, &current_CentralBank_agent->ecb_balance_sheet_calendar);
						if(rc != 0) { printf("Error: reading 'CentralBank' agent variable 'ecb_balance_sheet_calendar' of type 'ecb_balance_sheet_adt'\n"); exit(0); } }
					if(in_ecb_stocks_calendar) { j = 0;
						rc = read_ecb_stocks_adt(buffer, index, &j, &current_CentralBank_agent->ecb_stocks_calendar);
						if(rc != 0) { printf("Error: reading 'CentralBank' agent variable 'ecb_stocks_calendar' of type 'ecb_stocks_adt'\n"); exit(0); } }
					if(in_ecb_outflows_calendar) { j = 0;
						rc = read_ecb_outflows_adt(buffer, index, &j, &current_CentralBank_agent->ecb_outflows_calendar);
						if(rc != 0) { printf("Error: reading 'CentralBank' agent variable 'ecb_outflows_calendar' of type 'ecb_outflows_adt'\n"); exit(0); } }
					if(in_ecb_inflows_calendar) { j = 0;
						rc = read_ecb_inflows_adt(buffer, index, &j, &current_CentralBank_agent->ecb_inflows_calendar);
						if(rc != 0) { printf("Error: reading 'CentralBank' agent variable 'ecb_inflows_calendar' of type 'ecb_inflows_adt'\n"); exit(0); } }
					if(in_bond_holdings_value) { current_CentralBank_agent->bond_holdings_value = atof(buffer); }
					if(in_nr_gov_bonds) { current_CentralBank_agent->nr_gov_bonds = atoi(buffer); }
					if(in_fiat_money_govs) { current_CentralBank_agent->fiat_money_govs = atof(buffer); }
					if(in_fiat_money_bond_govs) { current_CentralBank_agent->fiat_money_bond_govs = atof(buffer); }
					if(in_bank_interest) { current_CentralBank_agent->bank_interest = atof(buffer); }
					if(in_gov_interest) { current_CentralBank_agent->gov_interest = atof(buffer); }
					if(in_gov_bond_purchase) { current_CentralBank_agent->gov_bond_purchase = atof(buffer); }
					if(in_total_income) { current_CentralBank_agent->total_income = atof(buffer); }
					if(in_total_expenses) { current_CentralBank_agent->total_expenses = atof(buffer); }
					if(in_total_assets) { current_CentralBank_agent->total_assets = atof(buffer); }
					if(in_total_liabilities) { current_CentralBank_agent->total_liabilities = atof(buffer); }
				 }else if(in_ClearingHouse_agent == 1)
				{
					if(in_id) { current_ClearingHouse_agent->id = atoi(buffer); }
					if(in_region_id) { current_ClearingHouse_agent->region_id = atoi(buffer); }
					if(in_partition_id) { current_ClearingHouse_agent->partition_id = atoi(buffer); }
					if(in_init_transient_period) { current_ClearingHouse_agent->init_transient_period = atoi(buffer); }
					if(in_pending_orders) { j = 0;
						rc = read_order_dynamic_array(buffer, index, &j, &current_ClearingHouse_agent->pending_orders);
						if(rc != 0) { printf("Error: reading 'ClearingHouse' agent variable 'pending_orders' of type 'order_array'\n"); exit(0); } }
					if(in_processed_orders) { j = 0;
						rc = read_order_dynamic_array(buffer, index, &j, &current_ClearingHouse_agent->processed_orders);
						if(rc != 0) { printf("Error: reading 'ClearingHouse' agent variable 'processed_orders' of type 'order_array'\n"); exit(0); } }
					if(in_stock_index) { j = 0;
						rc = read_index_adt(buffer, index, &j, &current_ClearingHouse_agent->stock_index);
						if(rc != 0) { printf("Error: reading 'ClearingHouse' agent variable 'stock_index' of type 'index_adt'\n"); exit(0); } }
					if(in_dsratio) { current_ClearingHouse_agent->dsratio = atof(buffer); }
					if(in_random_numbers_normal) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_ClearingHouse_agent->random_numbers_normal);
						if(rc != 0) { printf("Error: reading 'ClearingHouse' agent variable 'random_numbers_normal' of type 'double_array'\n"); exit(0); } }
					if(in_monthly_counter_total_dividend) { current_ClearingHouse_agent->monthly_counter_total_dividend = atof(buffer); }
					if(in_stock_index_price) { current_ClearingHouse_agent->stock_index_price = atof(buffer); }
					if(in_house_auction) { j = 0;
						rc = read_auction_adt(buffer, index, &j, &current_ClearingHouse_agent->house_auction);
						if(rc != 0) { printf("Error: reading 'ClearingHouse' agent variable 'house_auction' of type 'auction_adt'\n"); exit(0); } }
					if(in_rental_auction) { j = 0;
						rc = read_auction_adt(buffer, index, &j, &current_ClearingHouse_agent->rental_auction);
						if(rc != 0) { printf("Error: reading 'ClearingHouse' agent variable 'rental_auction' of type 'auction_adt'\n"); exit(0); } }
					if(in_init_tenants) { j = 0;
						rc = read_tenant_adt_dynamic_array(buffer, index, &j, &current_ClearingHouse_agent->init_tenants);
						if(rc != 0) { printf("Error: reading 'ClearingHouse' agent variable 'init_tenants' of type 'tenant_adt_array'\n"); exit(0); } }
					if(in_init_landlords) { j = 0;
						rc = read_int_dynamic_array(buffer, index, &j, &current_ClearingHouse_agent->init_landlords);
						if(rc != 0) { printf("Error: reading 'ClearingHouse' agent variable 'init_landlords' of type 'int_array'\n"); exit(0); } }
					if(in_init_owners) { j = 0;
						rc = read_int_dynamic_array(buffer, index, &j, &current_ClearingHouse_agent->init_owners);
						if(rc != 0) { printf("Error: reading 'ClearingHouse' agent variable 'init_owners' of type 'int_array'\n"); exit(0); } }
				 }else if(in_NSA_agent == 1)
				{
					if(in_id) { current_NSA_agent->id = atoi(buffer); }
					if(in_region_id) { current_NSA_agent->region_id = atoi(buffer); }
					if(in_partition_id) { current_NSA_agent->partition_id = atoi(buffer); }
					if(in_init_transient_period) { current_NSA_agent->init_transient_period = atoi(buffer); }
					if(in_network_banks) { j = 0;
						rc = read_node_adt_dynamic_array(buffer, index, &j, &current_NSA_agent->network_banks);
						if(rc != 0) { printf("Error: reading 'NSA' agent variable 'network_banks' of type 'node_adt_array'\n"); exit(0); } }
					if(in_network_firms) { j = 0;
						rc = read_node_adt_dynamic_array(buffer, index, &j, &current_NSA_agent->network_firms);
						if(rc != 0) { printf("Error: reading 'NSA' agent variable 'network_firms' of type 'node_adt_array'\n"); exit(0); } }
					if(in_network_hhs) { j = 0;
						rc = read_node_adt_dynamic_array(buffer, index, &j, &current_NSA_agent->network_hhs);
						if(rc != 0) { printf("Error: reading 'NSA' agent variable 'network_hhs' of type 'node_adt_array'\n"); exit(0); } }
					if(in_network) { j = 0;
						rc = read_node_adt_dynamic_array(buffer, index, &j, &current_NSA_agent->network);
						if(rc != 0) { printf("Error: reading 'NSA' agent variable 'network' of type 'node_adt_array'\n"); exit(0); } }
					if(in_total_no_loans_banks) { current_NSA_agent->total_no_loans_banks = atoi(buffer); }
					if(in_total_no_loans_firms) { current_NSA_agent->total_no_loans_firms = atoi(buffer); }
					if(in_total_no_loans_hh) { current_NSA_agent->total_no_loans_hh = atoi(buffer); }
					if(in_total_value_loans_banks) { current_NSA_agent->total_value_loans_banks = atof(buffer); }
					if(in_total_value_loans_firms) { current_NSA_agent->total_value_loans_firms = atof(buffer); }
					if(in_total_value_loans_hh) { current_NSA_agent->total_value_loans_hh = atof(buffer); }
					if(in_firm_loan_no_dist) { j = 0;
						rc = read_int_dynamic_array(buffer, index, &j, &current_NSA_agent->firm_loan_no_dist);
						if(rc != 0) { printf("Error: reading 'NSA' agent variable 'firm_loan_no_dist' of type 'int_array'\n"); exit(0); } }
					if(in_firm_loan_value_dist) { j = 0;
						rc = read_double_dynamic_array(buffer, index, &j, &current_NSA_agent->firm_loan_value_dist);
						if(rc != 0) { printf("Error: reading 'NSA' agent variable 'firm_loan_value_dist' of type 'double_array'\n"); exit(0); } }
					if(in_clustering_coefficient) { current_NSA_agent->clustering_coefficient = atof(buffer); }
					if(in_homophily_index) { current_NSA_agent->homophily_index = atof(buffer); }
					if(in_average_path_length) { current_NSA_agent->average_path_length = atof(buffer); }
					if(in_links) { current_NSA_agent->links = atoi(buffer); }
				 }
			}
			index = 0;
			buffer[index] = '\0';
		}
		else
		{
			buffer[index] = c;
			if(index < 99999) index++;
			else
			{
				printf("Error: agent reading buffer too small\n");
				printf("%s\n", buffer);
				exit(0);
			}
		}
	}
	/* Close file */
	(void)fclose(file);

	return 0;
}

/** \fn void check_location_exists(char * location)
 * \brief Check that a directory exists.
 * \param location The directory location to check.
 */
int check_location_exists(char * location)
{
	/* Save a dummy file to directory and remove.
	 * This checks directory exists and is writable */
	FILE * file;
	char * buffer;

	buffer = (char *)malloc( (strlen(location) + strlen("dummy.temp") + 1) * sizeof(char));
	strcpy(buffer, location);
	strcat(buffer, "dummy.temp");

	if((file = fopen(buffer, "w")) == NULL) return 0;

	(void)fclose(file);
	/* Remove dummy file */
	remove(buffer);

	return 1;
}


/** \fn void readinitialstates(char * filename, int * itno, xmachine ** agent_list, double cloud_data[6], int flag)
 * \brief Read initial X-machine memory starting values from a file.
 * \param filename The path to the file.
 * \param filelocation The directory of the location
 * \param itno Pointer to the iteration number.
 * \param agent_list List of agents in the model to be constructed by this function.
 * \param cloud_data Max and min x,y,z coordinates of agents.
 * \param partition_method Identifies partitioning method: 1 = geometric, 2 = round-robin
 * \param flag Flag for whether to check space partitions.
 */
void readinitialstates(char * filename, char * filelocation, int * itno, double cloud_data[],
					   int partition_method, int flag)
{
	/* Pointer to file */
	FILE *file;
	/* Char and char buffer for reading file to */
	char c = '\0';
	char buffer[100000];
	char FLAME_location[10000];
	char FLAME_format[10000];
	char FLAME_type[10000];
	FLAME_output * current_FLAME_output = NULL;

	/* Things for round-robin partitioning */
	int agent_count = 0;
	int number_partitions = 0;
	int geometric=1;
	int other=2;
	

	/* Cloud data array initialisation */
	# ifndef S_SPLINT_S
	cloud_data[0] = SPINF;
	cloud_data[1] = -SPINF;
	cloud_data[2] = SPINF;
	cloud_data[3] = -SPINF;
	cloud_data[4] = SPINF;
	cloud_data[5] = -SPINF;
	# endif

	/* Temporary node and head of associated agent list to allow adding agents */
	node_information temp_node;

	/* Pointer to x-memory for initial state data */
	/*xmachine * current_xmachine;*/
	/* Variables for checking tags */
	int reading = 1;
	int i = 0;
	int rc;
	int in_tag = 0;
	int in_itno = 0;
	int FLAME_in_imports = 0;
	int FLAME_in_import = 0;
	int FLAME_in_outputs = 0;
	int FLAME_in_output = 0;
	int FLAME_in_location = 0;
	int FLAME_in_format = 0;
	int FLAME_in_type = 0;
	int FLAME_in_time = 0;
	int FLAME_in_period = 0;
	int FLAME_in_phase = 0;
	int FLAME_in_name = 0;

	/* Initialise environment vars */
	FLAME_environment_variable_rnd_seed = 0;
	FLAME_environment_variable_GSL_RNG_SEED = 0.0;
	FLAME_environment_variable_total_regions = 0;
	FLAME_environment_variable_id_debug_probe = 0;
	FLAME_environment_variable_print_debug_id_probe = 0;
	FLAME_environment_variable_time_debug_probe = 0;
	FLAME_environment_variable_print_log = 0;
	FLAME_environment_variable_print_debug_bankruptcy = 0;
	FLAME_environment_variable_print_debug_eurostat = 0;
	FLAME_environment_variable_print_debug_ch = 0;
	FLAME_environment_variable_print_debug_afm = 0;
	FLAME_environment_variable_print_debug_afm_ch = 0;
	FLAME_environment_variable_print_debug_exp1 = 0;
	FLAME_environment_variable_print_debug_file_exp1 = 0;
	FLAME_environment_variable_print_debug_file_exp2 = 0;
	FLAME_environment_variable_policy_exp1 = 0;
	FLAME_environment_variable_print_debug_gov = 0;
	FLAME_environment_variable_print_debug_household = 0;
	FLAME_environment_variable_print_debug_credit = 0;
	FLAME_environment_variable_print_debug_nsa = 0;
	FLAME_environment_variable_print_debug_consumption = 0;
	FLAME_environment_variable_print_debug_finman = 0;
	FLAME_environment_variable_print_debug_production = 0;
	FLAME_environment_variable_print_debug_mall = 0;
	FLAME_environment_variable_print_debug = 0;
	FLAME_environment_variable_print_debug_market_research = 0;
	FLAME_environment_variable_print_debug_credit_risk_mngt = 0;
	FLAME_environment_variable_print_debug_credit_unittest = 0;
	FLAME_environment_variable_print_debug_housing = 0;
	FLAME_environment_variable_print_debug_housing_unittest = 0;
	FLAME_environment_variable_print_debug_rental = 0;
	FLAME_environment_variable_print_debug_rental_unittest = 0;
	FLAME_environment_variable_switch_behavioral_state_transitions_housing = 0;
	FLAME_environment_variable_print_debug_mortgage = 0;
	FLAME_environment_variable_print_debug_mortgage_hh = 0;
	FLAME_environment_variable_policy_exp_energy_shock = 0;
	FLAME_environment_variable_policy_exp_stabilization_subsidy = 0;
	FLAME_environment_variable_policy_exp_stabilization_tax = 0;
	FLAME_environment_variable_const_bankruptcy_idle_period = 0;
	FLAME_environment_variable_days_per_month = 0;
	FLAME_environment_variable_xml_cloned = 0;
	FLAME_environment_variable_transition_phase_innov = 0;
	FLAME_environment_variable_transition_phase_recap = 0;
	FLAME_environment_variable_const_init_transient_period = 0;
	FLAME_environment_variable_individual_learning = 0;
	FLAME_environment_variable_const_wage_wealth_ratio = 0.0;
	FLAME_environment_variable_const_income_tax_rate = 0.0;
	FLAME_environment_variable_gamma_const = 0.0;
	FLAME_environment_variable_gamma_quality = 0.0;
	FLAME_environment_variable_depreciation_rate = 0.0;
	FLAME_environment_variable_discont_rate = 0.0;
	FLAME_environment_variable_mark_up = 0.0;
	FLAME_environment_variable_lambda = 0.0;
	FLAME_environment_variable_target_savings_rate = 0.0;
	FLAME_environment_variable_carrol_consumption_parameter = 0.0;
	FLAME_environment_variable_quantil_normal_distribution = 0.0;
	FLAME_environment_variable_firm_planning_horizon = 0;
	FLAME_environment_variable_adaption_delivery_volume = 0.0;
	FLAME_environment_variable_inv_inertia = 0.0;
	FLAME_environment_variable_gamma_logit_vintage_choice = 0.0;
	FLAME_environment_variable_delta_logit_vintage_choice = 0.0;
	FLAME_environment_variable_housing_alpha = 0.0;
	FLAME_environment_variable_housing_beta = 0.0;
	FLAME_environment_variable_housing_gamma = 0.0;
	FLAME_environment_variable_const_mortgage_initial_risk_of_default = 0.0;
	FLAME_environment_variable_const_corporate_initial_risk_of_default = 0.0;
	FLAME_environment_variable_max_duration_firm_loans_arrears = 0;
	FLAME_environment_variable_max_duration_firm_loans_npl = 0;
	FLAME_environment_variable_max_duration_mortgage_loans_arrears = 0;
	FLAME_environment_variable_max_duration_mortgage_loans_npl = 0;
	FLAME_environment_variable_max_dsti_for_repayment = 0.0;
	FLAME_environment_variable_max_id = 0;
	FLAME_environment_variable_number_of_banks_to_apply = 0;
	FLAME_environment_variable_const_number_of_banks = 0;
	FLAME_environment_variable_const_installment_periods = 0;
	FLAME_environment_variable_const_bank_dividend_rate = 0.0;
	FLAME_environment_variable_bank_lambda = 0.0;
	FLAME_environment_variable_ecb_interest_rate = 0.0;
	FLAME_environment_variable_ecb_interest_rate_markdown = 0.0;
	FLAME_environment_variable_alfa = 0.0;
	FLAME_environment_variable_min_reserve_ratio = 0.0;
	FLAME_environment_variable_const_init_pd_corp = 0.0;
	FLAME_environment_variable_const_init_lgd_corp = 0.0;
	FLAME_environment_variable_const_init_pd_hh = 0.0;
	FLAME_environment_variable_const_init_lgd_hh = 0.0;
	FLAME_environment_variable_switch_bank_liquidity_full_rationing = 0;
	FLAME_environment_variable_switch_bank_capital_full_rationing = 0;
	FLAME_environment_variable_switch_non_risk_weighted_car = 0;
	FLAME_environment_variable_switch_ban_bank_dividends = 0;
	FLAME_environment_variable_switch_credit_rationing_unsound_firms = 0;
	FLAME_environment_variable_switch_credit_rationing_ponzi_firms = 0;
	FLAME_environment_variable_bank_data_quantile_upper_bound = 0.0;
	FLAME_environment_variable_bank_data_quantile_lower_bound = 0.0;
	FLAME_environment_variable_const_firm_leverage = 0.0;
	FLAME_environment_variable_debt_rescaling_factor = 0.0;
	FLAME_environment_variable_target_leverage_ratio = 0.0;
	FLAME_environment_variable_target_liquidity_ratio = 0.0;
	FLAME_environment_variable_const_dividend_earnings_ratio = 0.0;
	FLAME_environment_variable_switch_threshold_full_dividend_rule = 0;
	FLAME_environment_variable_const_threshold_full_dividend_rule = 0.0;
	FLAME_environment_variable_switch_firm_illiquidity_debt_rescaling_rule = 0;
	FLAME_environment_variable_igfirm_dividend_payout_stretching_month = 0;
	FLAME_environment_variable_index_price_adj = 0.0;
	FLAME_environment_variable_index_price_adj_max = 0.0;
	FLAME_environment_variable_index_price_adj_min = 0.0;
	FLAME_environment_variable_trading_activity = 0;
	FLAME_environment_variable_trading_random = 0;
	FLAME_environment_variable_igfirm_fin_man_debug = 0;
	FLAME_environment_variable_switch_igfirm_endogenous_innovation_probability = 0;
	FLAME_environment_variable_igfirm_exogenous_innovation_probability = 0.0;
	FLAME_environment_variable_power_of_end_probability_function = 0.0;
	FLAME_environment_variable_igfirm_producer_debug = 0;
	FLAME_environment_variable_igfirm_exogenous_productivity_progress = 0.0;
	FLAME_environment_variable_symmetric_shock = 0;
	FLAME_environment_variable_energy_shock_start = 0;
	FLAME_environment_variable_energy_shock_end = 0;
	FLAME_environment_variable_const_energy_shock_intensity = 0.0;
	FLAME_environment_variable_energy_shock_frequency = 0;
	FLAME_environment_variable_innovation_by_random = 0;
	FLAME_environment_variable_ig_good_limited_offer = 0;
	FLAME_environment_variable_max_offer_ig_good = 0;
	FLAME_environment_variable_initial_frontier_firm_transition_phase = 0.0;
	FLAME_environment_variable_initial_productivity_firm = 0.0;
	FLAME_environment_variable_initial_specific_skills = 0.0;
	FLAME_environment_variable_strenght_of_tech_progress = 0;
	FLAME_environment_variable_linear_combination_pricing_ig_good = 0.0;
	FLAME_environment_variable_initial_capital_price_wage_ratio = 0.0;
	FLAME_environment_variable_union_strength = 0.0;
	FLAME_environment_variable_wage_update = 0.0;
	FLAME_environment_variable_min_vacancy = 0;
	FLAME_environment_variable_wage_reservation_update = 0.0;
	FLAME_environment_variable_region_cost = 0.0;
	FLAME_environment_variable_delivery_prob_if_critical_stock_0 = 0.0;
	FLAME_environment_variable_number_applications = 0;
	FLAME_environment_variable_applications_per_day = 0;
	FLAME_environment_variable_lower_bound_firing = 0;
	FLAME_environment_variable_upper_bound_firing = 0;
	FLAME_environment_variable_logit_parameter_specific_skills = 0.0;
	FLAME_environment_variable_logit_parameter_general_skills = 0.0;
	FLAME_environment_variable_skill_update_acc_to_formula = 0;
	FLAME_environment_variable_gov_policy_unemployment_benefit_pct = 0.0;
	FLAME_environment_variable_gov_policy_money_financing_fraction = 0.0;
	FLAME_environment_variable_gov_policy_gdp_fraction_consumption = 0.0;
	FLAME_environment_variable_gov_policy_gdp_fraction_investment = 0.0;
	FLAME_environment_variable_no_regions_per_gov = 0;
	FLAME_environment_variable_subsidy_trigger_on = 0.0;
	FLAME_environment_variable_subsidy_trigger_off = 0.0;
	FLAME_environment_variable_gov_policy_swith_quantitative_easing = 0;
	FLAME_environment_variable_gov_policy_switch_human_capital_improvement = 0;
	FLAME_environment_variable_policy_exp_best_technology_subsidy = 0;
	FLAME_environment_variable_regional_policy_technology_subsidy = 0;
	FLAME_environment_variable_best_technology_subsidy_pct = 0.0;
	FLAME_environment_variable_innovation_switched_on = 0;
	FLAME_environment_variable_mr_start_price = 0.0;
	FLAME_environment_variable_mr_end_price = 0.0;
	FLAME_environment_variable_mr_price_increment = 0.0;
	FLAME_environment_variable_max_no_employees_product_innovation = 0;
	

	/* Open config file to read-only */
	if((file = fopen(filename, "r"))==NULL)
	{
		printf("Error: opening initial states '%s'\n", filename);
		exit(0);
	}
	
	/* Initialise variables */
    *itno = 0;





	if(partition_method==geometric) printf("xml: Geometric partitioning\n");
	else if(partition_method==other) printf("xml: Round-robin partitioning\n");
	else printf("xml: Error - invalid partitioning method\n");


	/* Set p_xmachine to the agent list passed in then new agents are added to this list
	 * Will be set to agent list for specific node is space partitions are already known (flag=1)
	 */
	/* If we're reading without knowing partitions already then use the dummy current node (it's not in the list of nodes)*/
	if (flag == 0) current_node = &temp_node;

	printf("Reading initial data file: %s\n", filename);
	/* Read file until end of xml */
	while(reading==1)
	{
		/* Get the next char from the file */
		c = (char)fgetc(file);

		/* If the end of a tag */
		if(c == '>')
		{
			/* Place 0 at end of buffer to make chars a string */
			buffer[i] = 0;

			if(strcmp(buffer, "states") == 0) reading = 1;
			if(strcmp(buffer, "/states") == 0) reading = 0;
			if(strcmp(buffer, "itno") == 0) in_itno = 1;
			if(strcmp(buffer, "/itno") == 0) in_itno = 0;
			if(strcmp(buffer, "imports") == 0) FLAME_in_imports = 1;
			if(strcmp(buffer, "/imports") == 0) FLAME_in_imports = 0;
			if(strcmp(buffer, "import") == 0)
			{
				/*FLAME_location[0] = '\0';*/
				strcpy(FLAME_location, filelocation);
				FLAME_format[0] = '\0';
				FLAME_type[0] = '\0';

				FLAME_in_import = 1;
			}
			if(strcmp(buffer, "/import") == 0)
			{
				if(strcmp("agent", FLAME_type) == 0 || strcmp("environment", FLAME_type) == 0)
				{
					if(strcmp("xml", FLAME_format) == 0)
					{
						if(strcmp("agent", FLAME_type) == 0) readAgentXML(FLAME_location, cloud_data, partition_method, flag, number_partitions, agent_count, itno);
						if(strcmp("environment", FLAME_type) == 0) readEnvironmentXML(FLAME_location);
					}
					else
					{
						printf("Error: import format '%s' is unsupported\n", FLAME_format);
						exit(0);
					}
				}
				else
				{
					printf("Error: import type '%s' is not agent or environment\n", FLAME_type);
					exit(0);
				}

				FLAME_in_import = 0;
			}
			if(strcmp(buffer, "location") == 0) FLAME_in_location = 1;
			if(strcmp(buffer, "/location") == 0) FLAME_in_location = 0;
			if(strcmp(buffer, "format") == 0) FLAME_in_format = 1;
			if(strcmp(buffer, "/format") == 0) FLAME_in_format = 0;
			if(strcmp(buffer, "type") == 0) FLAME_in_type = 1;
			if(strcmp(buffer, "/type") == 0) FLAME_in_type = 0;
			if(strcmp(buffer, "outputs") == 0) FLAME_in_outputs = 1;
			if(strcmp(buffer, "/outputs") == 0) FLAME_in_outputs = 0;
			if(strcmp(buffer, "output") == 0)
			{
				if(FLAME_in_outputs == 1)
				{
					current_FLAME_output = add_FLAME_output(&FLAME_outputs);
	
					FLAME_in_output = 1;
				}
			}
			if(strcmp(buffer, "/output") == 0)
			{
				if(FLAME_in_outputs == 1)
				{
					if(current_FLAME_output->type == -1)
					{
						printf("Error: an output type has not been set\n");
						exit(0);
					}
					if(current_FLAME_output->format == -1)
					{
						printf("Error: an output format has not been set\n");
						exit(0);
					}
					if(current_FLAME_output->location == NULL)
					{
						printf("Error: an output location has not been set\n");
						exit(0);
					}
					/* If type is xml check if location exists */
					if(current_FLAME_output->type == 0)
					{
						rc = check_location_exists(current_FLAME_output->location);
						if(rc == 0)
						{
							printf("Error: location directory '%s' does not exist\n", current_FLAME_output->location);
							exit(0);
						}
					}
					/* Period has to be larger than 0 */
					if(current_FLAME_output->period < 1)
					{
						printf("Error: output period is less than 1: '%d'\n", current_FLAME_output->period);
						exit(0);
					}
					/* Phase cannot be equal or larger than period */
					if(current_FLAME_output->phase >= current_FLAME_output->period)
					{
						printf("Error: output phase is more or equal to period: '%d'\n", current_FLAME_output->phase);
						exit(0);
					}
	
					FLAME_in_output = 0;
				}
			}
			if(strcmp(buffer, "time") == 0) FLAME_in_time = 1;
			if(strcmp(buffer, "/time") == 0) FLAME_in_time = 0;
			if(strcmp(buffer, "period") == 0) FLAME_in_period = 1;
			if(strcmp(buffer, "/period") == 0) FLAME_in_period = 0;
			if(strcmp(buffer, "phase") == 0) FLAME_in_phase = 1;
			if(strcmp(buffer, "/phase") == 0) FLAME_in_phase = 0;
			if(strcmp(buffer, "name") == 0) FLAME_in_name = 1;
			if(strcmp(buffer, "/name") == 0) FLAME_in_name = 0;

			/* End of tag and reset buffer */
			in_tag = 0;
			i = 0;
		}
		/* If start of tag */
		else if(c == '<')
		{
			/* Place /0 at end of buffer to end numbers */
			buffer[i] = 0;
			/* Flag in tag */
			in_tag = 1;

			if(in_itno) *itno = atoi(buffer);
			if(FLAME_in_imports == 1)
			{
				if(FLAME_in_import == 1)
				{
					if(FLAME_in_location == 1) strcat(FLAME_location, buffer);
					if(FLAME_in_format == 1) strcpy(FLAME_format, buffer);
					if(FLAME_in_type == 1) strcpy(FLAME_type, buffer);
				}
			}
			if(FLAME_in_outputs == 1)
			{
				if(FLAME_in_output == 1)
				{
					if(FLAME_in_type == 1)
					{
						if(strcmp("snapshot", buffer) == 0) current_FLAME_output->type = 0;
						else if(strcmp("agent", buffer) != 0)
						{
							printf("Error: output type is not 'snapshot' or an 'agent': '%s'\n", buffer);
							exit(0);
						}
					}
					if(FLAME_in_name == 1)
					{
						if(strcmp("Firm", buffer) == 0) current_FLAME_output->type = 1;
						else if(strcmp("Household", buffer) == 0) current_FLAME_output->type = 2;
						else if(strcmp("Mall", buffer) == 0) current_FLAME_output->type = 3;
						else if(strcmp("IGFirm", buffer) == 0) current_FLAME_output->type = 4;
						else if(strcmp("Eurostat", buffer) == 0) current_FLAME_output->type = 5;
						else if(strcmp("Bank", buffer) == 0) current_FLAME_output->type = 6;
						else if(strcmp("Government", buffer) == 0) current_FLAME_output->type = 7;
						else if(strcmp("CentralBank", buffer) == 0) current_FLAME_output->type = 8;
						else if(strcmp("ClearingHouse", buffer) == 0) current_FLAME_output->type = 9;
						else if(strcmp("NSA", buffer) == 0) current_FLAME_output->type = 10;
						else 
						{
							printf("Error: output name is not an agent name: '%s'\n", buffer);
							exit(0);
						}
					}
					if(FLAME_in_format == 1)
					{
						if(strcmp("xml", buffer) == 0) current_FLAME_output->format = 0;
						else
						{
							printf("Error: output format is unsupported: '%s'\n", buffer);
							exit(0);
						}
					}
					if(FLAME_in_location == 1)
					{
						current_FLAME_output->location = (char *)malloc( (strlen(filelocation) + strlen(buffer) + 1) * sizeof(char));
						strcpy(current_FLAME_output->location, filelocation);
						strcat(current_FLAME_output->location, buffer);
					}
					if(FLAME_in_time == 1)
					{
						if(FLAME_in_period == 1) current_FLAME_output->period = atoi(buffer);
						if(FLAME_in_phase == 1)  current_FLAME_output->phase = atoi(buffer);
					}
				}
			}
			/* Reset buffer */
			i = 0;
		}
		/* If in tag put read char into buffer */
		else if(in_tag == 1)
		{
			buffer[i] = c;
			i++;
		}
		/* If in data read char into buffer */
		else
		{
			buffer[i] = c;
			i++;
		}
	}

	/* Close the file */
	(void)fclose(file);

	/* Also try and read environment and agents from 0.xml */
	readEnvironmentXML(filename);
	readAgentXML(filename, cloud_data, partition_method, flag, number_partitions, agent_count, itno);

	/* If outputs is empty add default snapshot for every iteration */
	if(FLAME_outputs == NULL)
	{
		current_FLAME_output = add_FLAME_output(&FLAME_outputs);
		current_FLAME_output->type   = 0; /* snapshot */
		current_FLAME_output->format = 0; /* xml */
		current_FLAME_output->location = (char *)malloc( (strlen(filelocation) +  1) * sizeof(char));
		strcpy(current_FLAME_output->location, filelocation); /* location = 0.xml location */
		current_FLAME_output->period = 1; /* every iteration */
		current_FLAME_output->phase  = 0; /* no phase */
	}
	
	/* Print output settings to CLI */
	for(current_FLAME_output = FLAME_outputs; current_FLAME_output != NULL; current_FLAME_output = current_FLAME_output->next)
	{
		printf("output: type='");
		if(current_FLAME_output->type == 0) printf("snapshot");
		else if(current_FLAME_output->type == 1) printf("agent' name='Firm");
		else if(current_FLAME_output->type == 2) printf("agent' name='Household");
		else if(current_FLAME_output->type == 3) printf("agent' name='Mall");
		else if(current_FLAME_output->type == 4) printf("agent' name='IGFirm");
		else if(current_FLAME_output->type == 5) printf("agent' name='Eurostat");
		else if(current_FLAME_output->type == 6) printf("agent' name='Bank");
		else if(current_FLAME_output->type == 7) printf("agent' name='Government");
		else if(current_FLAME_output->type == 8) printf("agent' name='CentralBank");
		else if(current_FLAME_output->type == 9) printf("agent' name='ClearingHouse");
		else if(current_FLAME_output->type == 10) printf("agent' name='NSA");
		else printf("undefined");
		printf("' format='");
		if(current_FLAME_output->format == 0) printf("xml");
		else printf("undefined");
		printf("' location='%s'", current_FLAME_output->location);
		printf(" period='%d' phase='%d'\n", current_FLAME_output->period, current_FLAME_output->phase);
	}

	/* Make sure cloud data makes sense if any of x,y,z coords were all the same */
	if ( partition_method == geometric ) {
		if ( cloud_data[0] == cloud_data[1] ) {
			cloud_data[0] = -SPINF;
			cloud_data[1] = SPINF;
		}
		if ( cloud_data[2] == cloud_data[3] ) {
			cloud_data[2] = -SPINF;
			cloud_data[3] = SPINF;
		}
		if ( cloud_data[4] == cloud_data[5] ) {
			cloud_data[4] = -SPINF;
			cloud_data[5] = SPINF;
		}
	}
}

/** \fn void write_int_static_array(FILE *file, $name * temp)
 * \brief Writes int.
 */
void write_int_static_array(FILE *file, int * temp, int size)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<size; i++)
	{
		sprintf(data, "%i", temp[i]);
		fputs(data, file);
		if(i < size-1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_float_static_array(FILE *file, float * temp)
 * \brief Writes float.
 */
void write_float_static_array(FILE *file, float * temp, int size)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<size; i++)
	{
		sprintf(data, "%f", temp[i]);
		fputs(data, file);
		if(i < size-1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_double_static_array(FILE *file, double * temp)
 * \brief Writes double.
 */
void write_double_static_array(FILE *file, double * temp, int size)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<size; i++)
	{
		sprintf(data, "%f", temp[i]);
		fputs(data, file);
		if(i < size-1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_char_static_array(FILE *file, char * temp)
 * \brief Writes char.
 */
void write_char_static_array(FILE *file, char * temp, int size)
{
	int i;
	char data[1000];

	//fputs("{", file);
	for(i=0; i<size; i++)
	{
		sprintf(data, "%c", temp[i]);
		fputs(data, file);
		//if(i < size-1) fputs(", ", file);
	}
	//fputs("}", file);
}

/** \fn void write_int_dynamic_array(FILE *file, int_array* temp)
 * \brief Writes int.
 */
void write_int_dynamic_array(FILE *file, int_array * temp)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<(*temp).size; i++)
	{
		sprintf(data, "%i", (*temp).array[i]);
		fputs(data, file);
		if(i < ((*temp).size-1)) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_float_dynamic_array(FILE *file, float_array* temp)
 * \brief Writes float.
 */
void write_float_dynamic_array(FILE *file, float_array * temp)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<(*temp).size; i++)
	{
		sprintf(data, "%f", (*temp).array[i]);
		fputs(data, file);
		if(i < ((*temp).size-1)) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_double_dynamic_array(FILE *file, double_array* temp)
 * \brief Writes double.
 */
void write_double_dynamic_array(FILE *file, double_array * temp)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<(*temp).size; i++)
	{
		sprintf(data, "%f", (*temp).array[i]);
		fputs(data, file);
		if(i < ((*temp).size-1)) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_char_dynamic_array(FILE *file, char_array* temp)
 * \brief Writes char.
 */
void write_char_dynamic_array(FILE *file, char_array * temp)
{
	int i;
	char data[1000];

	for(i=0; i<(*temp).size; i++)
	{
		sprintf(data, "%c", (*temp).array[i]);
		fputs(data, file);
	}
}

/** \fn void write_consumption_request(FILE *file, consumption_request * temp_datatype)
 * \brief Writes consumption_request datatype.
 */
void write_consumption_request(FILE *file, consumption_request * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).worker_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).consumer_region_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).firm_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quantity);
	fputs(data, file);
	fputs("}", file);
}

void write_consumption_request_static_array(FILE *file, consumption_request * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_consumption_request(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_consumption_request_dynamic_array(FILE *file, consumption_request_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_consumption_request(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_mall_info(FILE *file, mall_info * temp_datatype)
 * \brief Writes mall_info datatype.
 */
void write_mall_info(FILE *file, mall_info * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).mall_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).critical_stock);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).current_stock);
	fputs(data, file);
	fputs("}", file);
}

void write_mall_info_static_array(FILE *file, mall_info * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_mall_info(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_mall_info_dynamic_array(FILE *file, mall_info_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_mall_info(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_mall_quality_price_info(FILE *file, mall_quality_price_info * temp_datatype)
 * \brief Writes mall_quality_price_info datatype.
 */
void write_mall_quality_price_info(FILE *file, mall_quality_price_info * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).mall_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).firm_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).mall_region_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quality);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).available);
	fputs(data, file);
	fputs("}", file);
}

void write_mall_quality_price_info_static_array(FILE *file, mall_quality_price_info * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_mall_quality_price_info(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_mall_quality_price_info_dynamic_array(FILE *file, mall_quality_price_info_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_mall_quality_price_info(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_mall_stock(FILE *file, mall_stock * temp_datatype)
 * \brief Writes mall_stock datatype.
 */
void write_mall_stock(FILE *file, mall_stock * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).firm_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).region_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).stock);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quality);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).previous_price);
	fputs(data, file);
	fputs("}", file);
}

void write_mall_stock_static_array(FILE *file, mall_stock * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_mall_stock(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_mall_stock_dynamic_array(FILE *file, mall_stock_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_mall_stock(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_delivery_volume_per_mall(FILE *file, delivery_volume_per_mall * temp_datatype)
 * \brief Writes delivery_volume_per_mall datatype.
 */
void write_delivery_volume_per_mall(FILE *file, delivery_volume_per_mall * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).mall_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quantity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quality);
	fputs(data, file);
	fputs("}", file);
}

void write_delivery_volume_per_mall_static_array(FILE *file, delivery_volume_per_mall * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_delivery_volume_per_mall(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_delivery_volume_per_mall_dynamic_array(FILE *file, delivery_volume_per_mall_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_delivery_volume_per_mall(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_logit_firm_id(FILE *file, logit_firm_id * temp_datatype)
 * \brief Writes logit_firm_id datatype.
 */
void write_logit_firm_id(FILE *file, logit_firm_id * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).logit);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).firm_id);
	fputs(data, file);
	fputs("}", file);
}

void write_logit_firm_id_static_array(FILE *file, logit_firm_id * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_logit_firm_id(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_logit_firm_id_dynamic_array(FILE *file, logit_firm_id_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_logit_firm_id(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_sales_in_mall(FILE *file, sales_in_mall * temp_datatype)
 * \brief Writes sales_in_mall datatype.
 */
void write_sales_in_mall(FILE *file, sales_in_mall * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).firm_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sales);
	fputs(data, file);
	fputs("}", file);
}

void write_sales_in_mall_static_array(FILE *file, sales_in_mall * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_sales_in_mall(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_sales_in_mall_dynamic_array(FILE *file, sales_in_mall_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_sales_in_mall(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_ordered_quantity(FILE *file, ordered_quantity * temp_datatype)
 * \brief Writes ordered_quantity datatype.
 */
void write_ordered_quantity(FILE *file, ordered_quantity * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).firm_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quantity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quality);
	fputs(data, file);
	fputs("}", file);
}

void write_ordered_quantity_static_array(FILE *file, ordered_quantity * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_ordered_quantity(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_ordered_quantity_dynamic_array(FILE *file, ordered_quantity_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_ordered_quantity(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_received_quantities(FILE *file, received_quantities * temp_datatype)
 * \brief Writes received_quantities datatype.
 */
void write_received_quantities(FILE *file, received_quantities * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).firm_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quantity);
	fputs(data, file);
	fputs("}", file);
}

void write_received_quantities_static_array(FILE *file, received_quantities * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_received_quantities(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_received_quantities_dynamic_array(FILE *file, received_quantities_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_received_quantities(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_sold_quantities_per_mall(FILE *file, sold_quantities_per_mall * temp_datatype)
 * \brief Writes sold_quantities_per_mall datatype.
 */
void write_sold_quantities_per_mall(FILE *file, sold_quantities_per_mall * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).mall_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sold_quantity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).stock_empty);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).estimated_demand);
	fputs(data, file);
	fputs("}", file);
}

void write_sold_quantities_per_mall_static_array(FILE *file, sold_quantities_per_mall * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_sold_quantities_per_mall(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_sold_quantities_per_mall_dynamic_array(FILE *file, sold_quantities_per_mall_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_sold_quantities_per_mall(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_data_type_sales(FILE *file, data_type_sales * temp_datatype)
 * \brief Writes data_type_sales datatype.
 */
void write_data_type_sales(FILE *file, data_type_sales * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).period);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sales);
	fputs(data, file);
	fputs("}", file);
}

void write_data_type_sales_static_array(FILE *file, data_type_sales * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_data_type_sales(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_data_type_sales_dynamic_array(FILE *file, data_type_sales_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_data_type_sales(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_sales_statistics(FILE *file, sales_statistics * temp_datatype)
 * \brief Writes sales_statistics datatype.
 */
void write_sales_statistics(FILE *file, sales_statistics * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).mall_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).region_id);
	fputs(data, file);
	fputs(", ", file);	write_data_type_sales_dynamic_array(file, &(*temp_datatype).sales);
	fputs("}", file);
}

void write_sales_statistics_static_array(FILE *file, sales_statistics * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_sales_statistics(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_sales_statistics_dynamic_array(FILE *file, sales_statistics_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_sales_statistics(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_adt_technology_vintages(FILE *file, adt_technology_vintages * temp_datatype)
 * \brief Writes adt_technology_vintages datatype.
 */
void write_adt_technology_vintages(FILE *file, adt_technology_vintages * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).productivity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sum_effective_productivities);
	fputs(data, file);
	fputs("}", file);
}

void write_adt_technology_vintages_static_array(FILE *file, adt_technology_vintages * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_adt_technology_vintages(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_adt_technology_vintages_dynamic_array(FILE *file, adt_technology_vintages_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_adt_technology_vintages(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_adt_capital_stock_vintages(FILE *file, adt_capital_stock_vintages * temp_datatype)
 * \brief Writes adt_capital_stock_vintages datatype.
 */
void write_adt_capital_stock_vintages(FILE *file, adt_capital_stock_vintages * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).amount);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).productivity);
	fputs(data, file);
	fputs("}", file);
}

void write_adt_capital_stock_vintages_static_array(FILE *file, adt_capital_stock_vintages * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_adt_capital_stock_vintages(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_adt_capital_stock_vintages_dynamic_array(FILE *file, adt_capital_stock_vintages_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_adt_capital_stock_vintages(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_financing_capital(FILE *file, financing_capital * temp_datatype)
 * \brief Writes financing_capital datatype.
 */
void write_financing_capital(FILE *file, financing_capital * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).financing_per_month);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).nr_periods_before_repayment);
	fputs(data, file);
	fputs("}", file);
}

void write_financing_capital_static_array(FILE *file, financing_capital * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_financing_capital(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_financing_capital_dynamic_array(FILE *file, financing_capital_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_financing_capital(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_temporary_sales_statistics(FILE *file, temporary_sales_statistics * temp_datatype)
 * \brief Writes temporary_sales_statistics datatype.
 */
void write_temporary_sales_statistics(FILE *file, temporary_sales_statistics * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).mall_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).period);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sales);
	fputs(data, file);
	fputs("}", file);
}

void write_temporary_sales_statistics_static_array(FILE *file, temporary_sales_statistics * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_temporary_sales_statistics(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_temporary_sales_statistics_dynamic_array(FILE *file, temporary_sales_statistics_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_temporary_sales_statistics(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_tenant_adt(FILE *file, tenant_adt * temp_datatype)
 * \brief Writes tenant_adt datatype.
 */
void write_tenant_adt(FILE *file, tenant_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).monthly_rent);
	fputs(data, file);
	fputs("}", file);
}

void write_tenant_adt_static_array(FILE *file, tenant_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_tenant_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_tenant_adt_dynamic_array(FILE *file, tenant_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_tenant_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_house_adt(FILE *file, house_adt * temp_datatype)
 * \brief Writes house_adt datatype.
 */
void write_house_adt(FILE *file, house_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).object_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).seller_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).buyer_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).value);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs("}", file);
}

void write_house_adt_static_array(FILE *file, house_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_house_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_house_adt_dynamic_array(FILE *file, house_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_house_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_foreclosure_adt(FILE *file, foreclosure_adt * temp_datatype)
 * \brief Writes foreclosure_adt datatype.
 */
void write_foreclosure_adt(FILE *file, foreclosure_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).object_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).former_owner_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).bank_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).value);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).claim);
	fputs(data, file);
	fputs("}", file);
}

void write_foreclosure_adt_static_array(FILE *file, foreclosure_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_foreclosure_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_foreclosure_adt_dynamic_array(FILE *file, foreclosure_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_foreclosure_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_rental_adt(FILE *file, rental_adt * temp_datatype)
 * \brief Writes rental_adt datatype.
 */
void write_rental_adt(FILE *file, rental_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).object_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).tenant_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).landlord_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).monthly_rent);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).sold);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).value);
	fputs(data, file);
	fputs("}", file);
}

void write_rental_adt_static_array(FILE *file, rental_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_rental_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_rental_adt_dynamic_array(FILE *file, rental_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_rental_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_mortgage_contract_adt(FILE *file, mortgage_contract_adt * temp_datatype)
 * \brief Writes mortgage_contract_adt datatype.
 */
void write_mortgage_contract_adt(FILE *file, mortgage_contract_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).household_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).bank_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).initial_duration);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).initial_principal);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).initial_loan_to_value);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).initial_total_interest);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).initial_risk_of_default);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).interest_rate_annual);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).current_duration);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).outstanding_principal);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).outstanding_interest);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).monthly_total_repayment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).monthly_principal);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).monthly_interest);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).current_risk_of_default);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).status);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).arrears_counter);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).npl_counter);
	fputs(data, file);
	fputs("}", file);
}

void write_mortgage_contract_adt_static_array(FILE *file, mortgage_contract_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_mortgage_contract_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_mortgage_contract_adt_dynamic_array(FILE *file, mortgage_contract_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_mortgage_contract_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_mortgage_application_adt(FILE *file, mortgage_application_adt * temp_datatype)
 * \brief Writes mortgage_application_adt datatype.
 */
void write_mortgage_application_adt(FILE *file, mortgage_application_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).household_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).annuity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).dstic);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sampled_loan_to_value);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).sampled_duration);
	fputs(data, file);
	fputs("}", file);
}

void write_mortgage_application_adt_static_array(FILE *file, mortgage_application_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_mortgage_application_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_mortgage_application_adt_dynamic_array(FILE *file, mortgage_application_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_mortgage_application_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_mortgage_sample_adt(FILE *file, mortgage_sample_adt * temp_datatype)
 * \brief Writes mortgage_sample_adt datatype.
 */
void write_mortgage_sample_adt(FILE *file, mortgage_sample_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).sampled_initial_principal);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).sampled_initial_duration);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sampled_outstanding_principal);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sampled_interest_rate_annual);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sampled_monthly_total_repayment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).sampled_percent_ownership);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sampled_value_at_acquisition);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sampled_initial_ltv);
	fputs(data, file);
	fputs("}", file);
}

void write_mortgage_sample_adt_static_array(FILE *file, mortgage_sample_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_mortgage_sample_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_mortgage_sample_adt_dynamic_array(FILE *file, mortgage_sample_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_mortgage_sample_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_sample_adt(FILE *file, sample_adt * temp_datatype)
 * \brief Writes sample_adt datatype.
 */
void write_sample_adt(FILE *file, sample_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).sampled_total_monthly_income);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sampled_monthly_rent);
	fputs(data, file);
	fputs("}", file);
}

void write_sample_adt_static_array(FILE *file, sample_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_sample_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_sample_adt_dynamic_array(FILE *file, sample_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_sample_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_debt_item(FILE *file, debt_item * temp_datatype)
 * \brief Writes debt_item datatype.
 */
void write_debt_item(FILE *file, debt_item * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).bank_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).loan_value);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).interest_rate);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).installment_amount);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).exposure_per_installment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).residual_exposure);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).bad_debt);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).nr_periods_before_repayment);
	fputs(data, file);
	fputs("}", file);
}

void write_debt_item_static_array(FILE *file, debt_item * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_debt_item(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_debt_item_dynamic_array(FILE *file, debt_item_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_debt_item(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_account_item(FILE *file, account_item * temp_datatype)
 * \brief Writes account_item datatype.
 */
void write_account_item(FILE *file, account_item * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account);
	fputs(data, file);
	fputs("}", file);
}

void write_account_item_static_array(FILE *file, account_item * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_account_item(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_account_item_dynamic_array(FILE *file, account_item_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_account_item(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_financial_data_adt(FILE *file, financial_data_adt * temp_datatype)
 * \brief Writes financial_data_adt datatype.
 */
void write_financial_data_adt(FILE *file, financial_data_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).equity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_assets);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_debt);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).equity_asset_ratio);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).debt_equity_ratio);
	fputs(data, file);
	fputs("}", file);
}

void write_financial_data_adt_static_array(FILE *file, financial_data_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_financial_data_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_financial_data_adt_dynamic_array(FILE *file, financial_data_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_financial_data_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_node_adt(FILE *file, node_adt * temp_datatype)
 * \brief Writes node_adt datatype.
 */
void write_node_adt(FILE *file, node_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).id);
	fputs(data, file);
	fputs(", ", file);	write_financial_data_adt(file, &(*temp_datatype).financial_data);
	fputs(", ", file);	write_debt_item_dynamic_array(file, &(*temp_datatype).loan_portfolio);
	fputs(", ", file);	write_int_dynamic_array(file, &(*temp_datatype).friend_id_list);
	fputs(", ", file);	sprintf(data, "%c", (*temp_datatype).type_of_node);
	fputs(data, file);
	fputs("}", file);
}

void write_node_adt_static_array(FILE *file, node_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_node_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_node_adt_dynamic_array(FILE *file, node_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_node_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_order(FILE *file, order * temp_datatype)
 * \brief Writes order datatype.
 */
void write_order(FILE *file, order * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).trader_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).value);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).quantity);
	fputs(data, file);
	fputs("}", file);
}

void write_order_static_array(FILE *file, order * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_order(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_order_dynamic_array(FILE *file, order_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_order(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_index_adt(FILE *file, index_adt * temp_datatype)
 * \brief Writes index_adt datatype.
 */
void write_index_adt(FILE *file, index_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).weight);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_dividend);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).dividend_per_share);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).nr_shares);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).moving_avg_price);
	fputs(data, file);
	fputs(", ", file);	write_double_dynamic_array(file, &(*temp_datatype).price_history);
	fputs("}", file);
}

void write_index_adt_static_array(FILE *file, index_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_index_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_index_adt_dynamic_array(FILE *file, index_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_index_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_index_portfolio(FILE *file, index_portfolio * temp_datatype)
 * \brief Writes index_portfolio datatype.
 */
void write_index_portfolio(FILE *file, index_portfolio * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).lastprice);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).units);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).moving_avg_price);
	fputs(data, file);
	fputs("}", file);
}

void write_index_portfolio_static_array(FILE *file, index_portfolio * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_index_portfolio(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_index_portfolio_dynamic_array(FILE *file, index_portfolio_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_index_portfolio(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_Belief(FILE *file, Belief * temp_datatype)
 * \brief Writes Belief datatype.
 */
void write_Belief(FILE *file, Belief * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).expected_dividend);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).expected_price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).expected_return);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).expected_volatility);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).last_price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).fraction_to_invest);
	fputs(data, file);
	fputs("}", file);
}

void write_Belief_static_array(FILE *file, Belief * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_Belief(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_Belief_dynamic_array(FILE *file, Belief_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_Belief(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_capital_good_request(FILE *file, capital_good_request * temp_datatype)
 * \brief Writes capital_good_request datatype.
 */
void write_capital_good_request(FILE *file, capital_good_request * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).firm_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).capital_good_order);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).vintage);
	fputs(data, file);
	fputs("}", file);
}

void write_capital_good_request_static_array(FILE *file, capital_good_request * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_capital_good_request(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_capital_good_request_dynamic_array(FILE *file, capital_good_request_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_capital_good_request(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_vintage(FILE *file, vintage * temp_datatype)
 * \brief Writes vintage datatype.
 */
void write_vintage(FILE *file, vintage * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).productivity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).discounted_productivity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sales);
	fputs(data, file);
	fputs("}", file);
}

void write_vintage_static_array(FILE *file, vintage * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_vintage(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_vintage_dynamic_array(FILE *file, vintage_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_vintage(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_adt_sales_per_vintage(FILE *file, adt_sales_per_vintage * temp_datatype)
 * \brief Writes adt_sales_per_vintage datatype.
 */
void write_adt_sales_per_vintage(FILE *file, adt_sales_per_vintage * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).productivity_of_vintage);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sales);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).revenue);
	fputs(data, file);
	fputs("}", file);
}

void write_adt_sales_per_vintage_static_array(FILE *file, adt_sales_per_vintage * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_adt_sales_per_vintage(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_adt_sales_per_vintage_dynamic_array(FILE *file, adt_sales_per_vintage_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_adt_sales_per_vintage(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_employee(FILE *file, employee * temp_datatype)
 * \brief Writes employee datatype.
 */
void write_employee(FILE *file, employee * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).region_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).wage);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).general_skill);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).specific_skill);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).specific_skill_before_learning);
	fputs(data, file);
	fputs("}", file);
}

void write_employee_static_array(FILE *file, employee * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_employee(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_employee_dynamic_array(FILE *file, employee_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_employee(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_vacancy(FILE *file, vacancy * temp_datatype)
 * \brief Writes vacancy datatype.
 */
void write_vacancy(FILE *file, vacancy * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).firm_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).region_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).wage_offer);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).job_type);
	fputs(data, file);
	fputs("}", file);
}

void write_vacancy_static_array(FILE *file, vacancy * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_vacancy(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_vacancy_dynamic_array(FILE *file, vacancy_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_vacancy(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_job_application(FILE *file, job_application * temp_datatype)
 * \brief Writes job_application datatype.
 */
void write_job_application(FILE *file, job_application * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).worker_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).region_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).general_skill);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).specific_skill);
	fputs(data, file);
	fputs("}", file);
}

void write_job_application_static_array(FILE *file, job_application * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_job_application(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_job_application_dynamic_array(FILE *file, job_application_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_job_application(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_job_offer(FILE *file, job_offer * temp_datatype)
 * \brief Writes job_offer datatype.
 */
void write_job_offer(FILE *file, job_offer * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).firm_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).region_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).wage_offer);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).job_type);
	fputs(data, file);
	fputs("}", file);
}

void write_job_offer_static_array(FILE *file, job_offer * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_job_offer(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_job_offer_dynamic_array(FILE *file, job_offer_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_job_offer(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_logit(FILE *file, logit * temp_datatype)
 * \brief Writes logit datatype.
 */
void write_logit(FILE *file, logit * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).logit_value);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).worker_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).general_skill);
	fputs(data, file);
	fputs("}", file);
}

void write_logit_static_array(FILE *file, logit * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_logit(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_logit_dynamic_array(FILE *file, logit_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_logit(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_adt_list_adaptation_speed(FILE *file, adt_list_adaptation_speed * temp_datatype)
 * \brief Writes adt_list_adaptation_speed datatype.
 */
void write_adt_list_adaptation_speed(FILE *file, adt_list_adaptation_speed * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).general_skill_level);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).adaptation_speed);
	fputs(data, file);
	fputs("}", file);
}

void write_adt_list_adaptation_speed_static_array(FILE *file, adt_list_adaptation_speed * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_adt_list_adaptation_speed(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_adt_list_adaptation_speed_dynamic_array(FILE *file, adt_list_adaptation_speed_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_adt_list_adaptation_speed(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_adt_skill_distribution(FILE *file, adt_skill_distribution * temp_datatype)
 * \brief Writes adt_skill_distribution datatype.
 */
void write_adt_skill_distribution(FILE *file, adt_skill_distribution * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).general_skill_group);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).percentage);
	fputs(data, file);
	fputs("}", file);
}

void write_adt_skill_distribution_static_array(FILE *file, adt_skill_distribution * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_adt_skill_distribution(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_adt_skill_distribution_dynamic_array(FILE *file, adt_skill_distribution_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_adt_skill_distribution(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_adt_actual_skill_distribution_with_ids(FILE *file, adt_actual_skill_distribution_with_ids * temp_datatype)
 * \brief Writes adt_actual_skill_distribution_with_ids datatype.
 */
void write_adt_actual_skill_distribution_with_ids(FILE *file, adt_actual_skill_distribution_with_ids * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).general_skill_group);
	fputs(data, file);
	fputs(", ", file);	write_int_dynamic_array(file, &(*temp_datatype).id_list);
	fputs("}", file);
}

void write_adt_actual_skill_distribution_with_ids_static_array(FILE *file, adt_actual_skill_distribution_with_ids * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_adt_actual_skill_distribution_with_ids(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_adt_actual_skill_distribution_with_ids_dynamic_array(FILE *file, adt_actual_skill_distribution_with_ids_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_adt_actual_skill_distribution_with_ids(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_price_index_adt(FILE *file, price_index_adt * temp_datatype)
 * \brief Writes price_index_adt datatype.
 */
void write_price_index_adt(FILE *file, price_index_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).mean);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sd);
	fputs(data, file);
	fputs("}", file);
}

void write_price_index_adt_static_array(FILE *file, price_index_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_price_index_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_price_index_adt_dynamic_array(FILE *file, price_index_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_price_index_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_household_data(FILE *file, household_data * temp_datatype)
 * \brief Writes household_data datatype.
 */
void write_household_data(FILE *file, household_data * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).region_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_households);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_households_skill_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_households_skill_2);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_households_skill_3);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_households_skill_4);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_households_skill_5);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employed);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employed_skill_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employed_skill_2);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employed_skill_3);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employed_skill_4);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employed_skill_5);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).unemployed);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_2);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_3);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_4);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_5);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).consumption_budget);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage_skill_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage_skill_2);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage_skill_3);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage_skill_4);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage_skill_5);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill_2);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill_3);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill_4);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill_5);
	fputs(data, file);
	fputs("}", file);
}

void write_household_data_static_array(FILE *file, household_data * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_household_data(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_household_data_dynamic_array(FILE *file, household_data_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_household_data(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_firm_data(FILE *file, firm_data * temp_datatype)
 * \brief Writes firm_data datatype.
 */
void write_firm_data(FILE *file, firm_data * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).region_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_firms);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_active_firms);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).vacancies);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employees);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employees_skill_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employees_skill_2);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employees_skill_3);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employees_skill_4);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employees_skill_5);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage_skill_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage_skill_2);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage_skill_3);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage_skill_4);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage_skill_5);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill_2);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill_3);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill_4);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_s_skill_5);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_earnings);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_debt);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_assets);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_equity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_debt_earnings_ratio);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_debt_equity_ratio);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).labour_share_ratio);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).monthly_sold_quantity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).monthly_output);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).monthly_revenue);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).monthly_planned_output);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).monthly_investment_value);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).investment_gdp_ratio);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).gdp);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).cpi);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).cpi_last_month);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_firm_births);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_firm_deaths);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).productivity_progress);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).productivity);
	fputs(data, file);
	fputs("}", file);
}

void write_firm_data_static_array(FILE *file, firm_data * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_firm_data(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_firm_data_dynamic_array(FILE *file, firm_data_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_firm_data(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_region_data_item(FILE *file, region_data_item * temp_datatype)
 * \brief Writes region_data_item datatype.
 */
void write_region_data_item(FILE *file, region_data_item * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).cpi);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).cpi_last_month);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).gdp);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).output);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_2);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_3);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_4);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_5);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_firms);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_active_firms);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_firm_births);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_firm_deaths);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).investment_value);
	fputs(data, file);
	fputs("}", file);
}

void write_region_data_item_static_array(FILE *file, region_data_item * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_region_data_item(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_region_data_item_dynamic_array(FILE *file, region_data_item_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_region_data_item(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_history_item(FILE *file, history_item * temp_datatype)
 * \brief Writes history_item datatype.
 */
void write_history_item(FILE *file, history_item * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).cpi);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).gdp);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).output);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_2);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_3);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_4);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_rate_skill_5);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_wage);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_firms);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_active_firms);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_firm_births);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_firm_deaths);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).investment_value);
	fputs(data, file);
	fputs(", ", file);	write_region_data_item_dynamic_array(file, &(*temp_datatype).region_data);
	fputs("}", file);
}

void write_history_item_static_array(FILE *file, history_item * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_history_item(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_history_item_dynamic_array(FILE *file, history_item_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_history_item(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_firm_stocks_adt(FILE *file, firm_stocks_adt * temp_datatype)
 * \brief Writes firm_stocks_adt datatype.
 */
void write_firm_stocks_adt(FILE *file, firm_stocks_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).payment_account);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_value_local_inventory);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_value_capital_stock);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_assets);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_debt);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).equity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_liabilities);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).current_shares_outstanding);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account_day_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account_day_20);
	fputs(data, file);
	fputs("}", file);
}

void write_firm_stocks_adt_static_array(FILE *file, firm_stocks_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_firm_stocks_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_firm_stocks_adt_dynamic_array(FILE *file, firm_stocks_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_firm_stocks_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_firm_outflows_adt(FILE *file, firm_outflows_adt * temp_datatype)
 * \brief Writes firm_outflows_adt datatype.
 */
void write_firm_outflows_adt(FILE *file, firm_outflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).labour_costs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).capital_costs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).energy_costs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).tax_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_debt_installment_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_interest_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_dividend_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).value_of_repurchased_shares);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_expenses);
	fputs(data, file);
	fputs("}", file);
}

void write_firm_outflows_adt_static_array(FILE *file, firm_outflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_firm_outflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_firm_outflows_adt_dynamic_array(FILE *file, firm_outflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_firm_outflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_firm_inflows_adt(FILE *file, firm_inflows_adt * temp_datatype)
 * \brief Writes firm_inflows_adt datatype.
 */
void write_firm_inflows_adt(FILE *file, firm_inflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).cum_revenue);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).new_loans);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).value_of_issued_shares);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).subsidy);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_income);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).deposit_interest);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).net_inflow);
	fputs(data, file);
	fputs("}", file);
}

void write_firm_inflows_adt_static_array(FILE *file, firm_inflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_firm_inflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_firm_inflows_adt_dynamic_array(FILE *file, firm_inflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_firm_inflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_household_stocks_adt(FILE *file, household_stocks_adt * temp_datatype)
 * \brief Writes household_stocks_adt datatype.
 */
void write_household_stocks_adt(FILE *file, household_stocks_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).payment_account);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).portfolio_value);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_assets);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_liabilities);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).nr_assets);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account_day_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account_day_20);
	fputs(data, file);
	fputs(", ", file);	write_mortgage_contract_adt(file, &(*temp_datatype).mortgage_main_residence);
	fputs(", ", file);	write_mortgage_contract_adt(file, &(*temp_datatype).mortgage_other_property);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_real_estate_value);
	fputs(data, file);
	fputs(", ", file);	write_house_adt(file, &(*temp_datatype).main_residence);
	fputs(", ", file);	write_house_adt(file, &(*temp_datatype).other_property);
	fputs(", ", file);	write_rental_adt_dynamic_array(file, &(*temp_datatype).rental_property_list);
	fputs("}", file);
}

void write_household_stocks_adt_static_array(FILE *file, household_stocks_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_household_stocks_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_household_stocks_adt_dynamic_array(FILE *file, household_stocks_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_household_stocks_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_household_outflows_adt(FILE *file, household_outflows_adt * temp_datatype)
 * \brief Writes household_outflows_adt datatype.
 */
void write_household_outflows_adt(FILE *file, household_outflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).consumption_expenditure);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).tax_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).restitution_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).asset_purchases);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).mortgage_debt_service);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).rents);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_expenses);
	fputs(data, file);
	fputs("}", file);
}

void write_household_outflows_adt_static_array(FILE *file, household_outflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_household_outflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_household_outflows_adt_dynamic_array(FILE *file, household_outflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_household_outflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_household_inflows_adt(FILE *file, household_inflows_adt * temp_datatype)
 * \brief Writes household_inflows_adt datatype.
 */
void write_household_inflows_adt(FILE *file, household_inflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).wage);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).unemployment_benefit);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).subsidies);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).transfer);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).gov_interest);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).asset_sales);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_dividends);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).deposit_interest);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_income);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).mortgage_debt_service);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).mortgage_loan);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).rents);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).net_inflow);
	fputs(data, file);
	fputs("}", file);
}

void write_household_inflows_adt_static_array(FILE *file, household_inflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_household_inflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_household_inflows_adt_dynamic_array(FILE *file, household_inflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_household_inflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_bank_stocks_adt(FILE *file, bank_stocks_adt * temp_datatype)
 * \brief Writes bank_stocks_adt datatype.
 */
void write_bank_stocks_adt(FILE *file, bank_stocks_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).cash);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).reserves);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).regulatory_reserves);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_credit);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_assets);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).deposits);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).ecb_debt);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).equity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_liabilities);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).current_shares_outstanding);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).cash_day_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).cash_day_20);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).loan_loss_reserve_firm_loans);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).loan_loss_reserve_mortgage_loans);
	fputs(data, file);
	fputs(", ", file);	write_mortgage_contract_adt_dynamic_array(file, &(*temp_datatype).mortgage_portfolio);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_mortgages);
	fputs(data, file);
	fputs("}", file);
}

void write_bank_stocks_adt_static_array(FILE *file, bank_stocks_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_bank_stocks_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_bank_stocks_adt_dynamic_array(FILE *file, bank_stocks_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_bank_stocks_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_bank_outflows_adt(FILE *file, bank_outflows_adt * temp_datatype)
 * \brief Writes bank_outflows_adt datatype.
 */
void write_bank_outflows_adt(FILE *file, bank_outflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).firm_loan_issues);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).debt_installment_to_ecb);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).ecb_interest_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).deposit_interest_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).dividend_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).tax_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).deposit_outflow);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_expenses);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).mortgage_loan_issues);
	fputs(data, file);
	fputs("}", file);
}

void write_bank_outflows_adt_static_array(FILE *file, bank_outflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_bank_outflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_bank_outflows_adt_dynamic_array(FILE *file, bank_outflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_bank_outflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_bank_inflows_adt(FILE *file, bank_inflows_adt * temp_datatype)
 * \brief Writes bank_inflows_adt datatype.
 */
void write_bank_inflows_adt(FILE *file, bank_inflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).firm_loan_installments);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).firm_interest_payments);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).new_ecb_debt);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).deposit_inflow);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_income);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).net_inflow);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).net_deposit_inflow);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).mortgage_payments);
	fputs(data, file);
	fputs("}", file);
}

void write_bank_inflows_adt_static_array(FILE *file, bank_inflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_bank_inflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_bank_inflows_adt_dynamic_array(FILE *file, bank_inflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_bank_inflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_gov_stocks_adt(FILE *file, gov_stocks_adt * temp_datatype)
 * \brief Writes gov_stocks_adt datatype.
 */
void write_gov_stocks_adt(FILE *file, gov_stocks_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).payment_account);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_assets);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).value_bonds_outstanding);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).ecb_money);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).equity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_liabilities);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).nr_bonds_outstanding);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account_day_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account_day_20);
	fputs(data, file);
	fputs("}", file);
}

void write_gov_stocks_adt_static_array(FILE *file, gov_stocks_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_gov_stocks_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_gov_stocks_adt_dynamic_array(FILE *file, gov_stocks_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_gov_stocks_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_gov_outflows_adt(FILE *file, gov_outflows_adt * temp_datatype)
 * \brief Writes gov_outflows_adt datatype.
 */
void write_gov_outflows_adt(FILE *file, gov_outflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).investment_expenditure);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).consumption_expenditure);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).benefit_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).subsidy_payment_household);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).subsidy_payment_firm);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).transfer_payment_household);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).transfer_payment_firm);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).bond_interest_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).debt_installment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_bond_repurchase);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_expenses);
	fputs(data, file);
	fputs("}", file);
}

void write_gov_outflows_adt_static_array(FILE *file, gov_outflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_gov_outflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_gov_outflows_adt_dynamic_array(FILE *file, gov_outflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_gov_outflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_gov_inflows_adt(FILE *file, gov_inflows_adt * temp_datatype)
 * \brief Writes gov_inflows_adt datatype.
 */
void write_gov_inflows_adt(FILE *file, gov_inflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).tax_revenues);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).restitution_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_bond_financing);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_money_financing);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).ecb_dividend);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_income);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).net_inflow);
	fputs(data, file);
	fputs("}", file);
}

void write_gov_inflows_adt_static_array(FILE *file, gov_inflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_gov_inflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_gov_inflows_adt_dynamic_array(FILE *file, gov_inflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_gov_inflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_ecb_stocks_adt(FILE *file, ecb_stocks_adt * temp_datatype)
 * \brief Writes ecb_stocks_adt datatype.
 */
void write_ecb_stocks_adt(FILE *file, ecb_stocks_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).cash);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).gov_bond_holdings);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).fiat_money);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).fiat_money_banks);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).fiat_money_govs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_assets);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account_banks);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account_govs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).perpetuities_firms);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).perpetuities_banks);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).perpetuities_govs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).equity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_liabilities);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).nr_gov_bonds);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).equity_day_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).fiat_money_govs_bond);
	fputs(data, file);
	fputs("}", file);
}

void write_ecb_stocks_adt_static_array(FILE *file, ecb_stocks_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_ecb_stocks_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_ecb_stocks_adt_dynamic_array(FILE *file, ecb_stocks_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_ecb_stocks_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_ecb_outflows_adt(FILE *file, ecb_outflows_adt * temp_datatype)
 * \brief Writes ecb_outflows_adt datatype.
 */
void write_ecb_outflows_adt(FILE *file, ecb_outflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).gov_bond_purchase);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).bank_fiat_money);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).bank_deposits);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).gov_deposits);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).dividend_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_expenses);
	fputs(data, file);
	fputs("}", file);
}

void write_ecb_outflows_adt_static_array(FILE *file, ecb_outflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_ecb_outflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_ecb_outflows_adt_dynamic_array(FILE *file, ecb_outflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_ecb_outflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_ecb_inflows_adt(FILE *file, ecb_inflows_adt * temp_datatype)
 * \brief Writes ecb_inflows_adt datatype.
 */
void write_ecb_inflows_adt(FILE *file, ecb_inflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).bank_interest);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).bank_debt_installment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).gov_interest);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).bank_deposits);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).gov_deposits);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_income);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).net_inflow);
	fputs(data, file);
	fputs("}", file);
}

void write_ecb_inflows_adt_static_array(FILE *file, ecb_inflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_ecb_inflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_ecb_inflows_adt_dynamic_array(FILE *file, ecb_inflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_ecb_inflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_firm_balance_sheet_adt(FILE *file, firm_balance_sheet_adt * temp_datatype)
 * \brief Writes firm_balance_sheet_adt datatype.
 */
void write_firm_balance_sheet_adt(FILE *file, firm_balance_sheet_adt * temp_datatype)
{
	

	fputs("{", file);
	write_firm_stocks_adt(file, &(*temp_datatype).stocks);
	fputs(", ", file);	write_firm_outflows_adt(file, &(*temp_datatype).outflows);
	fputs(", ", file);	write_firm_inflows_adt(file, &(*temp_datatype).inflows);
	fputs("}", file);
}

void write_firm_balance_sheet_adt_static_array(FILE *file, firm_balance_sheet_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_firm_balance_sheet_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_firm_balance_sheet_adt_dynamic_array(FILE *file, firm_balance_sheet_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_firm_balance_sheet_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_household_balance_sheet_adt(FILE *file, household_balance_sheet_adt * temp_datatype)
 * \brief Writes household_balance_sheet_adt datatype.
 */
void write_household_balance_sheet_adt(FILE *file, household_balance_sheet_adt * temp_datatype)
{
	

	fputs("{", file);
	write_household_stocks_adt(file, &(*temp_datatype).stocks);
	fputs(", ", file);	write_household_outflows_adt(file, &(*temp_datatype).outflows);
	fputs(", ", file);	write_household_inflows_adt(file, &(*temp_datatype).inflows);
	fputs("}", file);
}

void write_household_balance_sheet_adt_static_array(FILE *file, household_balance_sheet_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_household_balance_sheet_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_household_balance_sheet_adt_dynamic_array(FILE *file, household_balance_sheet_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_household_balance_sheet_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_bank_balance_sheet_adt(FILE *file, bank_balance_sheet_adt * temp_datatype)
 * \brief Writes bank_balance_sheet_adt datatype.
 */
void write_bank_balance_sheet_adt(FILE *file, bank_balance_sheet_adt * temp_datatype)
{
	

	fputs("{", file);
	write_bank_stocks_adt(file, &(*temp_datatype).stocks);
	fputs(", ", file);	write_bank_outflows_adt(file, &(*temp_datatype).outflows);
	fputs(", ", file);	write_bank_inflows_adt(file, &(*temp_datatype).inflows);
	fputs("}", file);
}

void write_bank_balance_sheet_adt_static_array(FILE *file, bank_balance_sheet_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_bank_balance_sheet_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_bank_balance_sheet_adt_dynamic_array(FILE *file, bank_balance_sheet_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_bank_balance_sheet_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_gov_balance_sheet_adt(FILE *file, gov_balance_sheet_adt * temp_datatype)
 * \brief Writes gov_balance_sheet_adt datatype.
 */
void write_gov_balance_sheet_adt(FILE *file, gov_balance_sheet_adt * temp_datatype)
{
	

	fputs("{", file);
	write_gov_stocks_adt(file, &(*temp_datatype).stocks);
	fputs(", ", file);	write_gov_outflows_adt(file, &(*temp_datatype).outflows);
	fputs(", ", file);	write_gov_inflows_adt(file, &(*temp_datatype).inflows);
	fputs("}", file);
}

void write_gov_balance_sheet_adt_static_array(FILE *file, gov_balance_sheet_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_gov_balance_sheet_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_gov_balance_sheet_adt_dynamic_array(FILE *file, gov_balance_sheet_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_gov_balance_sheet_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_ecb_balance_sheet_adt(FILE *file, ecb_balance_sheet_adt * temp_datatype)
 * \brief Writes ecb_balance_sheet_adt datatype.
 */
void write_ecb_balance_sheet_adt(FILE *file, ecb_balance_sheet_adt * temp_datatype)
{
	

	fputs("{", file);
	write_ecb_stocks_adt(file, &(*temp_datatype).stocks);
	fputs(", ", file);	write_ecb_outflows_adt(file, &(*temp_datatype).outflows);
	fputs(", ", file);	write_ecb_inflows_adt(file, &(*temp_datatype).inflows);
	fputs("}", file);
}

void write_ecb_balance_sheet_adt_static_array(FILE *file, ecb_balance_sheet_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_ecb_balance_sheet_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_ecb_balance_sheet_adt_dynamic_array(FILE *file, ecb_balance_sheet_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_ecb_balance_sheet_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_igfirm_stocks_adt(FILE *file, igfirm_stocks_adt * temp_datatype)
 * \brief Writes igfirm_stocks_adt datatype.
 */
void write_igfirm_stocks_adt(FILE *file, igfirm_stocks_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).payment_account);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_value_local_inventory);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_value_capital_stock);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_assets);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_debt);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).equity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_liabilities);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).current_shares_outstanding);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account_day_1);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account_day_20);
	fputs(data, file);
	fputs("}", file);
}

void write_igfirm_stocks_adt_static_array(FILE *file, igfirm_stocks_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_igfirm_stocks_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_igfirm_stocks_adt_dynamic_array(FILE *file, igfirm_stocks_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_igfirm_stocks_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_igfirm_outflows_adt(FILE *file, igfirm_outflows_adt * temp_datatype)
 * \brief Writes igfirm_outflows_adt datatype.
 */
void write_igfirm_outflows_adt(FILE *file, igfirm_outflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).labour_costs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).capital_costs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).energy_costs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).tax_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_debt_installment_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_interest_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_dividend_payment);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).value_of_repurchased_shares);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_expenses);
	fputs(data, file);
	fputs("}", file);
}

void write_igfirm_outflows_adt_static_array(FILE *file, igfirm_outflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_igfirm_outflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_igfirm_outflows_adt_dynamic_array(FILE *file, igfirm_outflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_igfirm_outflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_igfirm_inflows_adt(FILE *file, igfirm_inflows_adt * temp_datatype)
 * \brief Writes igfirm_inflows_adt datatype.
 */
void write_igfirm_inflows_adt(FILE *file, igfirm_inflows_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).cum_revenue);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).new_loans);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).value_of_issued_shares);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).subsidy);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).total_income);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).deposit_interest);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).net_inflow);
	fputs(data, file);
	fputs("}", file);
}

void write_igfirm_inflows_adt_static_array(FILE *file, igfirm_inflows_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_igfirm_inflows_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_igfirm_inflows_adt_dynamic_array(FILE *file, igfirm_inflows_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_igfirm_inflows_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_igfirm_balance_sheet_adt(FILE *file, igfirm_balance_sheet_adt * temp_datatype)
 * \brief Writes igfirm_balance_sheet_adt datatype.
 */
void write_igfirm_balance_sheet_adt(FILE *file, igfirm_balance_sheet_adt * temp_datatype)
{
	

	fputs("{", file);
	write_igfirm_stocks_adt(file, &(*temp_datatype).stocks);
	fputs(", ", file);	write_igfirm_outflows_adt(file, &(*temp_datatype).outflows);
	fputs(", ", file);	write_igfirm_inflows_adt(file, &(*temp_datatype).inflows);
	fputs("}", file);
}

void write_igfirm_balance_sheet_adt_static_array(FILE *file, igfirm_balance_sheet_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_igfirm_balance_sheet_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_igfirm_balance_sheet_adt_dynamic_array(FILE *file, igfirm_balance_sheet_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_igfirm_balance_sheet_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_consumption_goods_offer(FILE *file, consumption_goods_offer * temp_datatype)
 * \brief Writes consumption_goods_offer datatype.
 */
void write_consumption_goods_offer(FILE *file, consumption_goods_offer * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quality);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs("}", file);
}

void write_consumption_goods_offer_static_array(FILE *file, consumption_goods_offer * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_consumption_goods_offer(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_consumption_goods_offer_dynamic_array(FILE *file, consumption_goods_offer_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_consumption_goods_offer(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_estimators_linear_regression(FILE *file, estimators_linear_regression * temp_datatype)
 * \brief Writes estimators_linear_regression datatype.
 */
void write_estimators_linear_regression(FILE *file, estimators_linear_regression * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).mall_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).region_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).intercept);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).regressor);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).variance);
	fputs(data, file);
	fputs("}", file);
}

void write_estimators_linear_regression_static_array(FILE *file, estimators_linear_regression * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_estimators_linear_regression(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_estimators_linear_regression_dynamic_array(FILE *file, estimators_linear_regression_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_estimators_linear_regression(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_estimated_values_adt(FILE *file, estimated_values_adt * temp_datatype)
 * \brief Writes estimated_values_adt datatype.
 */
void write_estimated_values_adt(FILE *file, estimated_values_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).no_positive_response);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).probability);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).estimated_fix_costs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).estimated_variable_costs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).estimated_earnings);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).additional_capital_Investments_depreciated);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).mean_specific_skills);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).mean_wage);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).no_employees);
	fputs(data, file);
	fputs("}", file);
}

void write_estimated_values_adt_static_array(FILE *file, estimated_values_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_estimated_values_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_estimated_values_adt_dynamic_array(FILE *file, estimated_values_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_estimated_values_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_market_research_price(FILE *file, dt_market_research_price * temp_datatype)
 * \brief Writes dt_market_research_price datatype.
 */
void write_dt_market_research_price(FILE *file, dt_market_research_price * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).price_change);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs(", ", file);	write_estimated_values_adt_dynamic_array(file, &(*temp_datatype).estimated_values);
	fputs("}", file);
}

void write_dt_market_research_price_static_array(FILE *file, dt_market_research_price * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_market_research_price(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_market_research_price_dynamic_array(FILE *file, dt_market_research_price_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_market_research_price(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_market_research_qualities(FILE *file, dt_market_research_qualities * temp_datatype)
 * \brief Writes dt_market_research_qualities datatype.
 */
void write_dt_market_research_qualities(FILE *file, dt_market_research_qualities * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).quality);
	fputs(data, file);
	fputs(", ", file);	write_dt_market_research_price_dynamic_array(file, &(*temp_datatype).market_research_price);
	fputs("}", file);
}

void write_dt_market_research_qualities_static_array(FILE *file, dt_market_research_qualities * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_market_research_qualities(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_market_research_qualities_dynamic_array(FILE *file, dt_market_research_qualities_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_market_research_qualities(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_best_price_strategies(FILE *file, dt_best_price_strategies * temp_datatype)
 * \brief Writes dt_best_price_strategies datatype.
 */
void write_dt_best_price_strategies(FILE *file, dt_best_price_strategies * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).quality);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).expected_earnings);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sum_earnings);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sum_expected_earnings_discounted);
	fputs(data, file);
	fputs("}", file);
}

void write_dt_best_price_strategies_static_array(FILE *file, dt_best_price_strategies * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_best_price_strategies(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_best_price_strategies_dynamic_array(FILE *file, dt_best_price_strategies_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_best_price_strategies(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_price_range(FILE *file, dt_price_range * temp_datatype)
 * \brief Writes dt_price_range datatype.
 */
void write_dt_price_range(FILE *file, dt_price_range * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).start_price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).end_price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).increment);
	fputs(data, file);
	fputs("}", file);
}

void write_dt_price_range_static_array(FILE *file, dt_price_range * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_price_range(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_price_range_dynamic_array(FILE *file, dt_price_range_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_price_range(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_prospective_variables(FILE *file, dt_prospective_variables * temp_datatype)
 * \brief Writes dt_prospective_variables datatype.
 */
void write_dt_prospective_variables(FILE *file, dt_prospective_variables * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).mean_specific_skills);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).estimated_mean_wage);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).no_employees);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).earnings);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).payment_account);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).buffer);
	fputs(data, file);
	fputs(", ", file);	write_adt_capital_stock_vintages_dynamic_array(file, &(*temp_datatype).capital_stock_vintages);
	fputs(", ", file);	write_financing_capital_dynamic_array(file, &(*temp_datatype).capital_financing);
	fputs(", ", file);	write_debt_item_dynamic_array(file, &(*temp_datatype).loans);
	fputs("}", file);
}

void write_dt_prospective_variables_static_array(FILE *file, dt_prospective_variables * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_prospective_variables(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_prospective_variables_dynamic_array(FILE *file, dt_prospective_variables_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_prospective_variables(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_variables_changed(FILE *file, dt_variables_changed * temp_datatype)
 * \brief Writes dt_variables_changed datatype.
 */
void write_dt_variables_changed(FILE *file, dt_variables_changed * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).price_index);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quality_index);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).productivity_progress);
	fputs(data, file);
	fputs("}", file);
}

void write_dt_variables_changed_static_array(FILE *file, dt_variables_changed * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_variables_changed(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_variables_changed_dynamic_array(FILE *file, dt_variables_changed_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_variables_changed(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_innovation_choice(FILE *file, dt_innovation_choice * temp_datatype)
 * \brief Writes dt_innovation_choice datatype.
 */
void write_dt_innovation_choice(FILE *file, dt_innovation_choice * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).development_period);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).employees_needed);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quality);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).expected_discounted_earnings);
	fputs(data, file);
	fputs("}", file);
}

void write_dt_innovation_choice_static_array(FILE *file, dt_innovation_choice * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_innovation_choice(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_innovation_choice_dynamic_array(FILE *file, dt_innovation_choice_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_innovation_choice(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_demand_function(FILE *file, dt_demand_function * temp_datatype)
 * \brief Writes dt_demand_function datatype.
 */
void write_dt_demand_function(FILE *file, dt_demand_function * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).quality);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).year);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).factor);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).exponent);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).variance);
	fputs(data, file);
	fputs("}", file);
}

void write_dt_demand_function_static_array(FILE *file, dt_demand_function * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_demand_function(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_demand_function_dynamic_array(FILE *file, dt_demand_function_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_demand_function(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_price_quantity_touple(FILE *file, dt_price_quantity_touple * temp_datatype)
 * \brief Writes dt_price_quantity_touple datatype.
 */
void write_dt_price_quantity_touple(FILE *file, dt_price_quantity_touple * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).quantity);
	fputs(data, file);
	fputs("}", file);
}

void write_dt_price_quantity_touple_static_array(FILE *file, dt_price_quantity_touple * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_price_quantity_touple(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_price_quantity_touple_dynamic_array(FILE *file, dt_price_quantity_touple_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_price_quantity_touple(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_market_size(FILE *file, dt_market_size * temp_datatype)
 * \brief Writes dt_market_size datatype.
 */
void write_dt_market_size(FILE *file, dt_market_size * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).period);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).market_size);
	fputs(data, file);
	fputs("}", file);
}

void write_dt_market_size_static_array(FILE *file, dt_market_size * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_market_size(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_market_size_dynamic_array(FILE *file, dt_market_size_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_market_size(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_total_and_regional_market_size(FILE *file, dt_total_and_regional_market_size * temp_datatype)
 * \brief Writes dt_total_and_regional_market_size datatype.
 */
void write_dt_total_and_regional_market_size(FILE *file, dt_total_and_regional_market_size * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).region_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).mall_id);
	fputs(data, file);
	fputs(", ", file);	write_dt_market_size_dynamic_array(file, &(*temp_datatype).market_sizes);
	fputs("}", file);
}

void write_dt_total_and_regional_market_size_static_array(FILE *file, dt_total_and_regional_market_size * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_total_and_regional_market_size(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_total_and_regional_market_size_dynamic_array(FILE *file, dt_total_and_regional_market_size_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_total_and_regional_market_size(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_value_lattice(FILE *file, dt_value_lattice * temp_datatype)
 * \brief Writes dt_value_lattice datatype.
 */
void write_dt_value_lattice(FILE *file, dt_value_lattice * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).intermediate_quality);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).value);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).strategy);
	fputs(data, file);
	fputs("}", file);
}

void write_dt_value_lattice_static_array(FILE *file, dt_value_lattice * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_value_lattice(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_value_lattice_dynamic_array(FILE *file, dt_value_lattice_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_value_lattice(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_value_lattice_years(FILE *file, dt_value_lattice_years * temp_datatype)
 * \brief Writes dt_value_lattice_years datatype.
 */
void write_dt_value_lattice_years(FILE *file, dt_value_lattice_years * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).year);
	fputs(data, file);
	fputs(", ", file);	write_dt_value_lattice_dynamic_array(file, &(*temp_datatype).values);
	fputs("}", file);
}

void write_dt_value_lattice_years_static_array(FILE *file, dt_value_lattice_years * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_value_lattice_years(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_value_lattice_years_dynamic_array(FILE *file, dt_value_lattice_years_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_value_lattice_years(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_dt_monthly_estimations(FILE *file, dt_monthly_estimations * temp_datatype)
 * \brief Writes dt_monthly_estimations datatype.
 */
void write_dt_monthly_estimations(FILE *file, dt_monthly_estimations * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%f", (*temp_datatype).output);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).earnings);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).sold_quantity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).labor_costs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).capital_costs);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).interest_payments);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).wage);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).mean_specific_skills);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).average_productivity);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).investment_nominal);
	fputs(data, file);
	fputs("}", file);
}

void write_dt_monthly_estimations_static_array(FILE *file, dt_monthly_estimations * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_dt_monthly_estimations(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_dt_monthly_estimations_dynamic_array(FILE *file, dt_monthly_estimations_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_dt_monthly_estimations(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_bid_adt(FILE *file, bid_adt * temp_datatype)
 * \brief Writes bid_adt datatype.
 */
void write_bid_adt(FILE *file, bid_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs("}", file);
}

void write_bid_adt_static_array(FILE *file, bid_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_bid_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_bid_adt_dynamic_array(FILE *file, bid_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_bid_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_ask_adt(FILE *file, ask_adt * temp_datatype)
 * \brief Writes ask_adt datatype.
 */
void write_ask_adt(FILE *file, ask_adt * temp_datatype)
{
	char data[1000];

	fputs("{", file);
	sprintf(data, "%i", (*temp_datatype).object_id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%i", (*temp_datatype).id);
	fputs(data, file);
	fputs(", ", file);	sprintf(data, "%f", (*temp_datatype).price);
	fputs(data, file);
	fputs("}", file);
}

void write_ask_adt_static_array(FILE *file, ask_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_ask_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_ask_adt_dynamic_array(FILE *file, ask_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_ask_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_auction_orders_adt(FILE *file, auction_orders_adt * temp_datatype)
 * \brief Writes auction_orders_adt datatype.
 */
void write_auction_orders_adt(FILE *file, auction_orders_adt * temp_datatype)
{
	

	fputs("{", file);
	write_bid_adt_dynamic_array(file, &(*temp_datatype).bids);
	fputs(", ", file);	write_ask_adt_dynamic_array(file, &(*temp_datatype).asks);
	fputs("}", file);
}

void write_auction_orders_adt_static_array(FILE *file, auction_orders_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_auction_orders_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_auction_orders_adt_dynamic_array(FILE *file, auction_orders_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_auction_orders_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_auction_adt(FILE *file, auction_adt * temp_datatype)
 * \brief Writes auction_adt datatype.
 */
void write_auction_adt(FILE *file, auction_adt * temp_datatype)
{
	

	fputs("{", file);
	write_auction_orders_adt(file, &(*temp_datatype).pending);
	fputs(", ", file);	write_auction_orders_adt(file, &(*temp_datatype).unprocessed);
	fputs("}", file);
}

void write_auction_adt_static_array(FILE *file, auction_adt * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_auction_adt(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_auction_adt_dynamic_array(FILE *file, auction_adt_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_auction_adt(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}



void write_Firm_agent(FILE *file, xmachine_memory_Firm * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>Firm</name>\n", file);
		fputs("<a>", file);
	sprintf(data, "%i", current->id);
	fputs(data, file);
	fputs("</a>\n", file);

	fputs("</xagent>\n", file);
}

void write_Household_agent(FILE *file, xmachine_memory_Household * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>Household</name>\n", file);
		fputs("<id>", file);
	sprintf(data, "%i", current->id);
	fputs(data, file);
	fputs("</id>\n", file);
		fputs("<region_id>", file);
	sprintf(data, "%i", current->region_id);
	fputs(data, file);
	fputs("</region_id>\n", file);
		fputs("<neighboring_region_ids>", file);
	write_int_dynamic_array(file, &current->neighboring_region_ids);
	fputs("</neighboring_region_ids>\n", file);
		fputs("<gov_id>", file);
	sprintf(data, "%i", current->gov_id);
	fputs(data, file);
	fputs("</gov_id>\n", file);
		fputs("<day_of_month_to_act>", file);
	sprintf(data, "%i", current->day_of_month_to_act);
	fputs(data, file);
	fputs("</day_of_month_to_act>\n", file);
		fputs("<payment_account>", file);
	sprintf(data, "%f", current->payment_account);
	fputs(data, file);
	fputs("</payment_account>\n", file);
		fputs("<bank_id>", file);
	sprintf(data, "%i", current->bank_id);
	fputs(data, file);
	fputs("</bank_id>\n", file);
		fputs("<partition_id>", file);
	sprintf(data, "%i", current->partition_id);
	fputs(data, file);
	fputs("</partition_id>\n", file);
		fputs("<init_transient_period>", file);
	sprintf(data, "%i", current->init_transient_period);
	fputs(data, file);
	fputs("</init_transient_period>\n", file);
		fputs("<consumption_budget>", file);
	sprintf(data, "%f", current->consumption_budget);
	fputs(data, file);
	fputs("</consumption_budget>\n", file);
		fputs("<housing_budget>", file);
	sprintf(data, "%f", current->housing_budget);
	fputs(data, file);
	fputs("</housing_budget>\n", file);
		fputs("<consumption_budget_in_month>", file);
	sprintf(data, "%f", current->consumption_budget_in_month);
	fputs(data, file);
	fputs("</consumption_budget_in_month>\n", file);
		fputs("<week_of_month>", file);
	sprintf(data, "%i", current->week_of_month);
	fputs(data, file);
	fputs("</week_of_month>\n", file);
		fputs("<weekly_budget>", file);
	sprintf(data, "%f", current->weekly_budget);
	fputs(data, file);
	fputs("</weekly_budget>\n", file);
		fputs("<rationed>", file);
	sprintf(data, "%i", current->rationed);
	fputs(data, file);
	fputs("</rationed>\n", file);
		fputs("<mall_completely_sold_out>", file);
	sprintf(data, "%i", current->mall_completely_sold_out);
	fputs(data, file);
	fputs("</mall_completely_sold_out>\n", file);
		fputs("<order_quantity>", file);
	write_ordered_quantity_static_array(file, current->order_quantity, 2);
	fputs("</order_quantity>\n", file);
		fputs("<received_quantity>", file);
	write_received_quantities_static_array(file, current->received_quantity, 2);
	fputs("</received_quantity>\n", file);
		fputs("<day_of_week_to_act>", file);
	sprintf(data, "%i", current->day_of_week_to_act);
	fputs(data, file);
	fputs("</day_of_week_to_act>\n", file);
		fputs("<day_of_month_receive_income>", file);
	sprintf(data, "%i", current->day_of_month_receive_income);
	fputs(data, file);
	fputs("</day_of_month_receive_income>\n", file);
		fputs("<current_productivity_employer>", file);
	sprintf(data, "%f", current->current_productivity_employer);
	fputs(data, file);
	fputs("</current_productivity_employer>\n", file);
		fputs("<current_mean_specific_skills_employer>", file);
	sprintf(data, "%f", current->current_mean_specific_skills_employer);
	fputs(data, file);
	fputs("</current_mean_specific_skills_employer>\n", file);
		fputs("<tax_payment>", file);
	sprintf(data, "%f", current->tax_payment);
	fputs(data, file);
	fputs("</tax_payment>\n", file);
		fputs("<cum_total_dividends>", file);
	sprintf(data, "%f", current->cum_total_dividends);
	fputs(data, file);
	fputs("</cum_total_dividends>\n", file);
		fputs("<tax_rate_hh_capital>", file);
	sprintf(data, "%f", current->tax_rate_hh_capital);
	fputs(data, file);
	fputs("</tax_rate_hh_capital>\n", file);
		fputs("<tax_rate_hh_labour>", file);
	sprintf(data, "%f", current->tax_rate_hh_labour);
	fputs(data, file);
	fputs("</tax_rate_hh_labour>\n", file);
		fputs("<price_index>", file);
	sprintf(data, "%f", current->price_index);
	fputs(data, file);
	fputs("</price_index>\n", file);
		fputs("<price_index_base_period>", file);
	sprintf(data, "%f", current->price_index_base_period);
	fputs(data, file);
	fputs("</price_index_base_period>\n", file);
		fputs("<commuting_costs_price_level_weight>", file);
	sprintf(data, "%f", current->commuting_costs_price_level_weight);
	fputs(data, file);
	fputs("</commuting_costs_price_level_weight>\n", file);
		fputs("<expenditures>", file);
	sprintf(data, "%f", current->expenditures);
	fputs(data, file);
	fputs("</expenditures>\n", file);
		fputs("<received_dividend>", file);
	sprintf(data, "%f", current->received_dividend);
	fputs(data, file);
	fputs("</received_dividend>\n", file);
		fputs("<received_dividend_in_calendar_month>", file);
	sprintf(data, "%f", current->received_dividend_in_calendar_month);
	fputs(data, file);
	fputs("</received_dividend_in_calendar_month>\n", file);
		fputs("<received_interest_daily>", file);
	sprintf(data, "%f", current->received_interest_daily);
	fputs(data, file);
	fputs("</received_interest_daily>\n", file);
		fputs("<received_interest_in_calendar_month>", file);
	sprintf(data, "%f", current->received_interest_in_calendar_month);
	fputs(data, file);
	fputs("</received_interest_in_calendar_month>\n", file);
		fputs("<flag_consumption_shifting>", file);
	sprintf(data, "%i", current->flag_consumption_shifting);
	fputs(data, file);
	fputs("</flag_consumption_shifting>\n", file);
		fputs("<excess_weekly_budget>", file);
	sprintf(data, "%f", current->excess_weekly_budget);
	fputs(data, file);
	fputs("</excess_weekly_budget>\n", file);
		fputs("<wealth_income_ratio_actual>", file);
	sprintf(data, "%f", current->wealth_income_ratio_actual);
	fputs(data, file);
	fputs("</wealth_income_ratio_actual>\n", file);
		fputs("<wealth_income_ratio_target>", file);
	sprintf(data, "%f", current->wealth_income_ratio_target);
	fputs(data, file);
	fputs("</wealth_income_ratio_target>\n", file);
		fputs("<last_weekly_budget>", file);
	sprintf(data, "%f", current->last_weekly_budget);
	fputs(data, file);
	fputs("</last_weekly_budget>\n", file);
		fputs("<have_mortgage>", file);
	sprintf(data, "%i", current->have_mortgage);
	fputs(data, file);
	fputs("</have_mortgage>\n", file);
		fputs("<hmr_mortgage_status>", file);
	sprintf(data, "%i", current->hmr_mortgage_status);
	fputs(data, file);
	fputs("</hmr_mortgage_status>\n", file);
		fputs("<op_mortgage_status>", file);
	sprintf(data, "%i", current->op_mortgage_status);
	fputs(data, file);
	fputs("</op_mortgage_status>\n", file);
		fputs("<request_mortgage>", file);
	sprintf(data, "%i", current->request_mortgage);
	fputs(data, file);
	fputs("</request_mortgage>\n", file);
		fputs("<mortgage_pay_day>", file);
	sprintf(data, "%i", current->mortgage_pay_day);
	fputs(data, file);
	fputs("</mortgage_pay_day>\n", file);
		fputs("<mortgage_sample_inputs>", file);
	write_mortgage_sample_adt_static_array(file, current->mortgage_sample_inputs, 6);
	fputs("</mortgage_sample_inputs>\n", file);
		fputs("<sample_inputs>", file);
	write_sample_adt(file, &current->sample_inputs);
	fputs("</sample_inputs>\n", file);
		fputs("<is_tenant>", file);
	sprintf(data, "%i", current->is_tenant);
	fputs(data, file);
	fputs("</is_tenant>\n", file);
		fputs("<is_owner>", file);
	sprintf(data, "%i", current->is_owner);
	fputs(data, file);
	fputs("</is_owner>\n", file);
		fputs("<is_landlord>", file);
	sprintf(data, "%i", current->is_landlord);
	fputs(data, file);
	fputs("</is_landlord>\n", file);
		fputs("<plan_stay_tenant>", file);
	sprintf(data, "%i", current->plan_stay_tenant);
	fputs(data, file);
	fputs("</plan_stay_tenant>\n", file);
		fputs("<plan_stay_owner>", file);
	sprintf(data, "%i", current->plan_stay_owner);
	fputs(data, file);
	fputs("</plan_stay_owner>\n", file);
		fputs("<plan_stay_landlord>", file);
	sprintf(data, "%i", current->plan_stay_landlord);
	fputs(data, file);
	fputs("</plan_stay_landlord>\n", file);
		fputs("<plan_sell_hmr>", file);
	sprintf(data, "%i", current->plan_sell_hmr);
	fputs(data, file);
	fputs("</plan_sell_hmr>\n", file);
		fputs("<plan_buy_hmr>", file);
	sprintf(data, "%i", current->plan_buy_hmr);
	fputs(data, file);
	fputs("</plan_buy_hmr>\n", file);
		fputs("<plan_rent_hmr>", file);
	sprintf(data, "%i", current->plan_rent_hmr);
	fputs(data, file);
	fputs("</plan_rent_hmr>\n", file);
		fputs("<plan_stop_rent_hmr>", file);
	sprintf(data, "%i", current->plan_stop_rent_hmr);
	fputs(data, file);
	fputs("</plan_stop_rent_hmr>\n", file);
		fputs("<plan_buy_op>", file);
	sprintf(data, "%i", current->plan_buy_op);
	fputs(data, file);
	fputs("</plan_buy_op>\n", file);
		fputs("<plan_sell_op>", file);
	sprintf(data, "%i", current->plan_sell_op);
	fputs(data, file);
	fputs("</plan_sell_op>\n", file);
		fputs("<plan_let_op>", file);
	sprintf(data, "%i", current->plan_let_op);
	fputs(data, file);
	fputs("</plan_let_op>\n", file);
		fputs("<plan_stop_let_op>", file);
	sprintf(data, "%i", current->plan_stop_let_op);
	fputs(data, file);
	fputs("</plan_stop_let_op>\n", file);
		fputs("<just_sold_hmr>", file);
	sprintf(data, "%i", current->just_sold_hmr);
	fputs(data, file);
	fputs("</just_sold_hmr>\n", file);
		fputs("<just_purchased_hmr>", file);
	sprintf(data, "%i", current->just_purchased_hmr);
	fputs(data, file);
	fputs("</just_purchased_hmr>\n", file);
		fputs("<just_purchased_op>", file);
	sprintf(data, "%i", current->just_purchased_op);
	fputs(data, file);
	fputs("</just_purchased_op>\n", file);
		fputs("<just_sold_op>", file);
	sprintf(data, "%i", current->just_sold_op);
	fputs(data, file);
	fputs("</just_sold_op>\n", file);
		fputs("<else_state>", file);
	sprintf(data, "%i", current->else_state);
	fputs(data, file);
	fputs("</else_state>\n", file);
		fputs("<other_states>", file);
	sprintf(data, "%i", current->other_states);
	fputs(data, file);
	fputs("</other_states>\n", file);
		fputs("<total_dsti>", file);
	sprintf(data, "%f", current->total_dsti);
	fputs(data, file);
	fputs("</total_dsti>\n", file);
		fputs("<rental_unit>", file);
	write_rental_adt(file, &current->rental_unit);
	fputs("</rental_unit>\n", file);
		fputs("<risk_free_rate>", file);
	sprintf(data, "%f", current->risk_free_rate);
	fputs(data, file);
	fputs("</risk_free_rate>\n", file);
		fputs("<wealth>", file);
	sprintf(data, "%f", current->wealth);
	fputs(data, file);
	fputs("</wealth>\n", file);
		fputs("<beliefs>", file);
	write_Belief(file, &current->beliefs);
	fputs("</beliefs>\n", file);
		fputs("<assetsowned>", file);
	write_index_portfolio(file, &current->assetsowned);
	fputs("</assetsowned>\n", file);
		fputs("<logit_beta>", file);
	sprintf(data, "%f", current->logit_beta);
	fputs(data, file);
	fputs("</logit_beta>\n", file);
		fputs("<wage>", file);
	sprintf(data, "%f", current->wage);
	fputs(data, file);
	fputs("</wage>\n", file);
		fputs("<wage_reservation>", file);
	sprintf(data, "%f", current->wage_reservation);
	fputs(data, file);
	fputs("</wage_reservation>\n", file);
		fputs("<general_skill>", file);
	sprintf(data, "%i", current->general_skill);
	fputs(data, file);
	fputs("</general_skill>\n", file);
		fputs("<list_adaptation_speed_per_general_skill_group>", file);
	write_adt_list_adaptation_speed_dynamic_array(file, &current->list_adaptation_speed_per_general_skill_group);
	fputs("</list_adaptation_speed_per_general_skill_group>\n", file);
		fputs("<on_the_job_search>", file);
	sprintf(data, "%i", current->on_the_job_search);
	fputs(data, file);
	fputs("</on_the_job_search>\n", file);
		fputs("<search_today>", file);
	sprintf(data, "%i", current->search_today);
	fputs(data, file);
	fputs("</search_today>\n", file);
		fputs("<last_labour_income>", file);
	sprintf(data, "%f", current->last_labour_income);
	fputs(data, file);
	fputs("</last_labour_income>\n", file);
		fputs("<specific_skill>", file);
	sprintf(data, "%f", current->specific_skill);
	fputs(data, file);
	fputs("</specific_skill>\n", file);
		fputs("<employee_firm_id>", file);
	sprintf(data, "%i", current->employee_firm_id);
	fputs(data, file);
	fputs("</employee_firm_id>\n", file);
		fputs("<just_employed>", file);
	sprintf(data, "%i", current->just_employed);
	fputs(data, file);
	fputs("</just_employed>\n", file);
		fputs("<just_unemployed>", file);
	sprintf(data, "%i", current->just_unemployed);
	fputs(data, file);
	fputs("</just_unemployed>\n", file);
		fputs("<start_unemployed>", file);
	sprintf(data, "%i", current->start_unemployed);
	fputs(data, file);
	fputs("</start_unemployed>\n", file);
		fputs("<start_employed>", file);
	sprintf(data, "%i", current->start_employed);
	fputs(data, file);
	fputs("</start_employed>\n", file);
		fputs("<unemployed_duration>", file);
	sprintf(data, "%i", current->unemployed_duration);
	fputs(data, file);
	fputs("</unemployed_duration>\n", file);
		fputs("<enter_matching>", file);
	sprintf(data, "%i", current->enter_matching);
	fputs(data, file);
	fputs("</enter_matching>\n", file);
		fputs("<employer_region_id>", file);
	sprintf(data, "%i", current->employer_region_id);
	fputs(data, file);
	fputs("</employer_region_id>\n", file);
		fputs("<employer_igfirm>", file);
	sprintf(data, "%i", current->employer_igfirm);
	fputs(data, file);
	fputs("</employer_igfirm>\n", file);
		fputs("<day_of_month_receive_benefit>", file);
	sprintf(data, "%i", current->day_of_month_receive_benefit);
	fputs(data, file);
	fputs("</day_of_month_receive_benefit>\n", file);
		fputs("<unemployment_payment>", file);
	sprintf(data, "%f", current->unemployment_payment);
	fputs(data, file);
	fputs("</unemployment_payment>\n", file);
		fputs("<region_wide_mean_wage>", file);
	sprintf(data, "%f", current->region_wide_mean_wage);
	fputs(data, file);
	fputs("</region_wide_mean_wage>\n", file);
		fputs("<last_net_income>", file);
	write_double_dynamic_array(file, &current->last_net_income);
	fputs("</last_net_income>\n", file);
		fputs("<mean_net_income>", file);
	sprintf(data, "%f", current->mean_net_income);
	fputs(data, file);
	fputs("</mean_net_income>\n", file);
		fputs("<monthly_income_vector>", file);
	write_double_dynamic_array(file, &current->monthly_income_vector);
	fputs("</monthly_income_vector>\n", file);
		fputs("<quarterly_income_vector>", file);
	write_double_dynamic_array(file, &current->quarterly_income_vector);
	fputs("</quarterly_income_vector>\n", file);
		fputs("<total_gross_monthly_income>", file);
	sprintf(data, "%f", current->total_gross_monthly_income);
	fputs(data, file);
	fputs("</total_gross_monthly_income>\n", file);
		fputs("<total_gross_quarterly_income>", file);
	sprintf(data, "%f", current->total_gross_quarterly_income);
	fputs(data, file);
	fputs("</total_gross_quarterly_income>\n", file);
		fputs("<household_balance_sheet_calendar>", file);
	write_household_balance_sheet_adt(file, &current->household_balance_sheet_calendar);
	fputs("</household_balance_sheet_calendar>\n", file);
		fputs("<household_stocks_calendar>", file);
	write_household_stocks_adt(file, &current->household_stocks_calendar);
	fputs("</household_stocks_calendar>\n", file);
		fputs("<household_outflows_calendar>", file);
	write_household_outflows_adt(file, &current->household_outflows_calendar);
	fputs("</household_outflows_calendar>\n", file);
		fputs("<household_inflows_calendar>", file);
	write_household_inflows_adt(file, &current->household_inflows_calendar);
	fputs("</household_inflows_calendar>\n", file);
		fputs("<unemployment_benefit_pct>", file);
	sprintf(data, "%f", current->unemployment_benefit_pct);
	fputs(data, file);
	fputs("</unemployment_benefit_pct>\n", file);
		fputs("<transfer_payment>", file);
	sprintf(data, "%f", current->transfer_payment);
	fputs(data, file);
	fputs("</transfer_payment>\n", file);
		fputs("<subsidy_pct>", file);
	sprintf(data, "%f", current->subsidy_pct);
	fputs(data, file);
	fputs("</subsidy_pct>\n", file);
		fputs("<total_income>", file);
	sprintf(data, "%f", current->total_income);
	fputs(data, file);
	fputs("</total_income>\n", file);
		fputs("<total_expenses>", file);
	sprintf(data, "%f", current->total_expenses);
	fputs(data, file);
	fputs("</total_expenses>\n", file);
		fputs("<total_assets>", file);
	sprintf(data, "%f", current->total_assets);
	fputs(data, file);
	fputs("</total_assets>\n", file);
		fputs("<total_liabilities>", file);
	sprintf(data, "%f", current->total_liabilities);
	fputs(data, file);
	fputs("</total_liabilities>\n", file);
		fputs("<monthly_consumption_expenditure>", file);
	sprintf(data, "%f", current->monthly_consumption_expenditure);
	fputs(data, file);
	fputs("</monthly_consumption_expenditure>\n", file);
		fputs("<monthly_bond_interest_income>", file);
	sprintf(data, "%f", current->monthly_bond_interest_income);
	fputs(data, file);
	fputs("</monthly_bond_interest_income>\n", file);
		fputs("<subsidy_payment>", file);
	sprintf(data, "%f", current->subsidy_payment);
	fputs(data, file);
	fputs("</subsidy_payment>\n", file);
		fputs("<region_mean_wage>", file);
	sprintf(data, "%f", current->region_mean_wage);
	fputs(data, file);
	fputs("</region_mean_wage>\n", file);
		fputs("<human_capital_policy_flag>", file);
	sprintf(data, "%i", current->human_capital_policy_flag);
	fputs(data, file);
	fputs("</human_capital_policy_flag>\n", file);
		fputs("<questionnaire_attending_propability>", file);
	sprintf(data, "%f", current->questionnaire_attending_propability);
	fputs(data, file);
	fputs("</questionnaire_attending_propability>\n", file);
		fputs("<willingness_to_attend>", file);
	sprintf(data, "%i", current->willingness_to_attend);
	fputs(data, file);
	fputs("</willingness_to_attend>\n", file);
		fputs("<interviewer_id>", file);
	sprintf(data, "%i", current->interviewer_id);
	fputs(data, file);
	fputs("</interviewer_id>\n", file);
		fputs("<random_no_test>", file);
	sprintf(data, "%i", current->random_no_test);
	fputs(data, file);
	fputs("</random_no_test>\n", file);
		fputs("<questionnaire>", file);
	write_int_static_array(file, current->questionnaire, 40);
	fputs("</questionnaire>\n", file);
		fputs("<current_price_quality_list>", file);
	write_consumption_goods_offer_dynamic_array(file, &current->current_price_quality_list);
	fputs("</current_price_quality_list>\n", file);
		fputs("<housing_bid_price>", file);
	sprintf(data, "%f", current->housing_bid_price);
	fputs(data, file);
	fputs("</housing_bid_price>\n", file);
		fputs("<housing_ask_price>", file);
	sprintf(data, "%f", current->housing_ask_price);
	fputs(data, file);
	fputs("</housing_ask_price>\n", file);
		fputs("<house>", file);
	write_house_adt(file, &current->house);
	fputs("</house>\n", file);
		fputs("<rent_bid_price>", file);
	sprintf(data, "%f", current->rent_bid_price);
	fputs(data, file);
	fputs("</rent_bid_price>\n", file);
		fputs("<rent_ask_price>", file);
	sprintf(data, "%f", current->rent_ask_price);
	fputs(data, file);
	fputs("</rent_ask_price>\n", file);
		fputs("<hmr_price_index>", file);
	write_price_index_adt(file, &current->hmr_price_index);
	fputs("</hmr_price_index>\n", file);
		fputs("<op_price_index>", file);
	write_price_index_adt(file, &current->op_price_index);
	fputs("</op_price_index>\n", file);
		fputs("<rent_price_index>", file);
	write_price_index_adt(file, &current->rent_price_index);
	fputs("</rent_price_index>\n", file);

	fputs("</xagent>\n", file);
}

void write_Mall_agent(FILE *file, xmachine_memory_Mall * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>Mall</name>\n", file);
		fputs("<id>", file);
	sprintf(data, "%i", current->id);
	fputs(data, file);
	fputs("</id>\n", file);
		fputs("<region_id>", file);
	sprintf(data, "%i", current->region_id);
	fputs(data, file);
	fputs("</region_id>\n", file);
		fputs("<gov_id>", file);
	sprintf(data, "%i", current->gov_id);
	fputs(data, file);
	fputs("</gov_id>\n", file);
		fputs("<partition_id>", file);
	sprintf(data, "%i", current->partition_id);
	fputs(data, file);
	fputs("</partition_id>\n", file);
		fputs("<init_transient_period>", file);
	sprintf(data, "%i", current->init_transient_period);
	fputs(data, file);
	fputs("</init_transient_period>\n", file);
		fputs("<current_stock>", file);
	write_mall_stock_dynamic_array(file, &current->current_stock);
	fputs("</current_stock>\n", file);
		fputs("<firm_revenues>", file);
	write_sales_in_mall_dynamic_array(file, &current->firm_revenues);
	fputs("</firm_revenues>\n", file);
		fputs("<total_supply>", file);
	sprintf(data, "%f", current->total_supply);
	fputs(data, file);
	fputs("</total_supply>\n", file);

	fputs("</xagent>\n", file);
}

void write_IGFirm_agent(FILE *file, xmachine_memory_IGFirm * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>IGFirm</name>\n", file);
		fputs("<id>", file);
	sprintf(data, "%i", current->id);
	fputs(data, file);
	fputs("</id>\n", file);
		fputs("<region_id>", file);
	sprintf(data, "%i", current->region_id);
	fputs(data, file);
	fputs("</region_id>\n", file);
		fputs("<gov_id>", file);
	sprintf(data, "%i", current->gov_id);
	fputs(data, file);
	fputs("</gov_id>\n", file);
		fputs("<bank_id>", file);
	sprintf(data, "%i", current->bank_id);
	fputs(data, file);
	fputs("</bank_id>\n", file);
		fputs("<day_of_month_to_act>", file);
	sprintf(data, "%i", current->day_of_month_to_act);
	fputs(data, file);
	fputs("</day_of_month_to_act>\n", file);
		fputs("<last_day_of_month_to_act>", file);
	sprintf(data, "%i", current->last_day_of_month_to_act);
	fputs(data, file);
	fputs("</last_day_of_month_to_act>\n", file);
		fputs("<payment_account>", file);
	sprintf(data, "%f", current->payment_account);
	fputs(data, file);
	fputs("</payment_account>\n", file);
		fputs("<payment_account_balance_sheet>", file);
	sprintf(data, "%f", current->payment_account_balance_sheet);
	fputs(data, file);
	fputs("</payment_account_balance_sheet>\n", file);
		fputs("<partition_id>", file);
	sprintf(data, "%i", current->partition_id);
	fputs(data, file);
	fputs("</partition_id>\n", file);
		fputs("<init_transient_period>", file);
	sprintf(data, "%i", current->init_transient_period);
	fputs(data, file);
	fputs("</init_transient_period>\n", file);
		fputs("<received_interest_daily>", file);
	sprintf(data, "%f", current->received_interest_daily);
	fputs(data, file);
	fputs("</received_interest_daily>\n", file);
		fputs("<received_interest_in_calendar_month>", file);
	sprintf(data, "%f", current->received_interest_in_calendar_month);
	fputs(data, file);
	fputs("</received_interest_in_calendar_month>\n", file);
		fputs("<ebit>", file);
	sprintf(data, "%f", current->ebit);
	fputs(data, file);
	fputs("</ebit>\n", file);
		fputs("<earnings>", file);
	sprintf(data, "%f", current->earnings);
	fputs(data, file);
	fputs("</earnings>\n", file);
		fputs("<tax_rate_corporate>", file);
	sprintf(data, "%f", current->tax_rate_corporate);
	fputs(data, file);
	fputs("</tax_rate_corporate>\n", file);
		fputs("<tax_rate_vat>", file);
	sprintf(data, "%f", current->tax_rate_vat);
	fputs(data, file);
	fputs("</tax_rate_vat>\n", file);
		fputs("<tax_payment>", file);
	sprintf(data, "%f", current->tax_payment);
	fputs(data, file);
	fputs("</tax_payment>\n", file);
		fputs("<tax_payment_in_calendar_month>", file);
	sprintf(data, "%f", current->tax_payment_in_calendar_month);
	fputs(data, file);
	fputs("</tax_payment_in_calendar_month>\n", file);
		fputs("<net_earnings>", file);
	sprintf(data, "%f", current->net_earnings);
	fputs(data, file);
	fputs("</net_earnings>\n", file);
		fputs("<previous_net_earnings>", file);
	sprintf(data, "%f", current->previous_net_earnings);
	fputs(data, file);
	fputs("</previous_net_earnings>\n", file);
		fputs("<total_dividend_payment>", file);
	sprintf(data, "%f", current->total_dividend_payment);
	fputs(data, file);
	fputs("</total_dividend_payment>\n", file);
		fputs("<total_dividend_payment_in_calendar_month>", file);
	sprintf(data, "%f", current->total_dividend_payment_in_calendar_month);
	fputs(data, file);
	fputs("</total_dividend_payment_in_calendar_month>\n", file);
		fputs("<current_share_price>", file);
	sprintf(data, "%f", current->current_share_price);
	fputs(data, file);
	fputs("</current_share_price>\n", file);
		fputs("<previous_dividend_per_share>", file);
	sprintf(data, "%f", current->previous_dividend_per_share);
	fputs(data, file);
	fputs("</previous_dividend_per_share>\n", file);
		fputs("<current_dividend_per_share>", file);
	sprintf(data, "%f", current->current_dividend_per_share);
	fputs(data, file);
	fputs("</current_dividend_per_share>\n", file);
		fputs("<previous_earnings_per_share>", file);
	sprintf(data, "%f", current->previous_earnings_per_share);
	fputs(data, file);
	fputs("</previous_earnings_per_share>\n", file);
		fputs("<current_earnings_per_share>", file);
	sprintf(data, "%f", current->current_earnings_per_share);
	fputs(data, file);
	fputs("</current_earnings_per_share>\n", file);
		fputs("<previous_dividend_per_earnings>", file);
	sprintf(data, "%f", current->previous_dividend_per_earnings);
	fputs(data, file);
	fputs("</previous_dividend_per_earnings>\n", file);
		fputs("<current_dividend_per_earnings>", file);
	sprintf(data, "%f", current->current_dividend_per_earnings);
	fputs(data, file);
	fputs("</current_dividend_per_earnings>\n", file);
		fputs("<debt_earnings_ratio>", file);
	sprintf(data, "%f", current->debt_earnings_ratio);
	fputs(data, file);
	fputs("</debt_earnings_ratio>\n", file);
		fputs("<debt_equity_ratio>", file);
	sprintf(data, "%f", current->debt_equity_ratio);
	fputs(data, file);
	fputs("</debt_equity_ratio>\n", file);
		fputs("<price_earnings_ratio>", file);
	sprintf(data, "%f", current->price_earnings_ratio);
	fputs(data, file);
	fputs("</price_earnings_ratio>\n", file);
		fputs("<retained_earnings_ratio>", file);
	sprintf(data, "%f", current->retained_earnings_ratio);
	fputs(data, file);
	fputs("</retained_earnings_ratio>\n", file);
		fputs("<earnings_per_share_ratio_growth>", file);
	sprintf(data, "%f", current->earnings_per_share_ratio_growth);
	fputs(data, file);
	fputs("</earnings_per_share_ratio_growth>\n", file);
		fputs("<critical_price_earnings_ratio>", file);
	sprintf(data, "%f", current->critical_price_earnings_ratio);
	fputs(data, file);
	fputs("</critical_price_earnings_ratio>\n", file);
		fputs("<critical_earnings_per_share_ratio>", file);
	sprintf(data, "%f", current->critical_earnings_per_share_ratio);
	fputs(data, file);
	fputs("</critical_earnings_per_share_ratio>\n", file);
		fputs("<total_debt>", file);
	sprintf(data, "%f", current->total_debt);
	fputs(data, file);
	fputs("</total_debt>\n", file);
		fputs("<total_debt_balance_sheet>", file);
	sprintf(data, "%f", current->total_debt_balance_sheet);
	fputs(data, file);
	fputs("</total_debt_balance_sheet>\n", file);
		fputs("<total_assets>", file);
	sprintf(data, "%f", current->total_assets);
	fputs(data, file);
	fputs("</total_assets>\n", file);
		fputs("<equity>", file);
	sprintf(data, "%f", current->equity);
	fputs(data, file);
	fputs("</equity>\n", file);
		fputs("<equity_balance_sheet>", file);
	sprintf(data, "%f", current->equity_balance_sheet);
	fputs(data, file);
	fputs("</equity_balance_sheet>\n", file);
		fputs("<earnings_per_share>", file);
	sprintf(data, "%f", current->earnings_per_share);
	fputs(data, file);
	fputs("</earnings_per_share>\n", file);
		fputs("<total_payments>", file);
	sprintf(data, "%f", current->total_payments);
	fputs(data, file);
	fputs("</total_payments>\n", file);
		fputs("<previous_shares_outstanding>", file);
	sprintf(data, "%i", current->previous_shares_outstanding);
	fputs(data, file);
	fputs("</previous_shares_outstanding>\n", file);
		fputs("<total_income>", file);
	sprintf(data, "%f", current->total_income);
	fputs(data, file);
	fputs("</total_income>\n", file);
		fputs("<total_liabilities>", file);
	sprintf(data, "%f", current->total_liabilities);
	fputs(data, file);
	fputs("</total_liabilities>\n", file);
		fputs("<total_expenses>", file);
	sprintf(data, "%f", current->total_expenses);
	fputs(data, file);
	fputs("</total_expenses>\n", file);
		fputs("<calc_production_costs>", file);
	sprintf(data, "%f", current->calc_production_costs);
	fputs(data, file);
	fputs("</calc_production_costs>\n", file);
		fputs("<productivity>", file);
	sprintf(data, "%f", current->productivity);
	fputs(data, file);
	fputs("</productivity>\n", file);
		fputs("<capital_good_price>", file);
	sprintf(data, "%f", current->capital_good_price);
	fputs(data, file);
	fputs("</capital_good_price>\n", file);
		fputs("<vintages>", file);
	write_vintage_dynamic_array(file, &current->vintages);
	fputs("</vintages>\n", file);
		fputs("<sales_per_vintage>", file);
	write_adt_sales_per_vintage_dynamic_array(file, &current->sales_per_vintage);
	fputs("</sales_per_vintage>\n", file);
		fputs("<mean_productivity_of_sales>", file);
	sprintf(data, "%f", current->mean_productivity_of_sales);
	fputs(data, file);
	fputs("</mean_productivity_of_sales>\n", file);
		fputs("<ratio_sold_productivity_best_practice>", file);
	sprintf(data, "%f", current->ratio_sold_productivity_best_practice);
	fputs(data, file);
	fputs("</ratio_sold_productivity_best_practice>\n", file);
		fputs("<igfirm_endogenous_innovation_probability>", file);
	sprintf(data, "%f", current->igfirm_endogenous_innovation_probability);
	fputs(data, file);
	fputs("</igfirm_endogenous_innovation_probability>\n", file);
		fputs("<revenue_per_day>", file);
	sprintf(data, "%f", current->revenue_per_day);
	fputs(data, file);
	fputs("</revenue_per_day>\n", file);
		fputs("<net_profit>", file);
	sprintf(data, "%f", current->net_profit);
	fputs(data, file);
	fputs("</net_profit>\n", file);
		fputs("<current_shares_outstanding>", file);
	sprintf(data, "%i", current->current_shares_outstanding);
	fputs(data, file);
	fputs("</current_shares_outstanding>\n", file);
		fputs("<energy_price_markup>", file);
	sprintf(data, "%f", current->energy_price_markup);
	fputs(data, file);
	fputs("</energy_price_markup>\n", file);
		fputs("<energy_costs_per_day>", file);
	sprintf(data, "%f", current->energy_costs_per_day);
	fputs(data, file);
	fputs("</energy_costs_per_day>\n", file);
		fputs("<earnings_per_day>", file);
	sprintf(data, "%f", current->earnings_per_day);
	fputs(data, file);
	fputs("</earnings_per_day>\n", file);
		fputs("<cum_energy_costs>", file);
	sprintf(data, "%f", current->cum_energy_costs);
	fputs(data, file);
	fputs("</cum_energy_costs>\n", file);
		fputs("<last_net_profits>", file);
	write_double_dynamic_array(file, &current->last_net_profits);
	fputs("</last_net_profits>\n", file);
		fputs("<mean_sales_last_months>", file);
	sprintf(data, "%f", current->mean_sales_last_months);
	fputs(data, file);
	fputs("</mean_sales_last_months>\n", file);
		fputs("<last_sales>", file);
	write_double_dynamic_array(file, &current->last_sales);
	fputs("</last_sales>\n", file);
		fputs("<dividend_payment>", file);
	sprintf(data, "%f", current->dividend_payment);
	fputs(data, file);
	fputs("</dividend_payment>\n", file);
		fputs("<duration_until_next_innovation>", file);
	sprintf(data, "%i", current->duration_until_next_innovation);
	fputs(data, file);
	fputs("</duration_until_next_innovation>\n", file);
		fputs("<unit_costs>", file);
	sprintf(data, "%f", current->unit_costs);
	fputs(data, file);
	fputs("</unit_costs>\n", file);
		fputs("<sales>", file);
	sprintf(data, "%f", current->sales);
	fputs(data, file);
	fputs("</sales>\n", file);
		fputs("<capital_good_demand>", file);
	sprintf(data, "%f", current->capital_good_demand);
	fputs(data, file);
	fputs("</capital_good_demand>\n", file);
		fputs("<capital_good_demand_last_month>", file);
	sprintf(data, "%f", current->capital_good_demand_last_month);
	fputs(data, file);
	fputs("</capital_good_demand_last_month>\n", file);
		fputs("<sales_last_month>", file);
	sprintf(data, "%f", current->sales_last_month);
	fputs(data, file);
	fputs("</sales_last_month>\n", file);
		fputs("<cum_revenue>", file);
	sprintf(data, "%f", current->cum_revenue);
	fputs(data, file);
	fputs("</cum_revenue>\n", file);
		fputs("<cum_revenue_last_month>", file);
	sprintf(data, "%f", current->cum_revenue_last_month);
	fputs(data, file);
	fputs("</cum_revenue_last_month>\n", file);
		fputs("<innovation_sheme_low_progress>", file);
	write_int_dynamic_array(file, &current->innovation_sheme_low_progress);
	fputs("</innovation_sheme_low_progress>\n", file);
		fputs("<innovation_sheme_medium_progress>", file);
	write_int_dynamic_array(file, &current->innovation_sheme_medium_progress);
	fputs("</innovation_sheme_medium_progress>\n", file);
		fputs("<innovation_sheme_high_progress>", file);
	write_int_dynamic_array(file, &current->innovation_sheme_high_progress);
	fputs("</innovation_sheme_high_progress>\n", file);
		fputs("<mean_general_skills>", file);
	sprintf(data, "%f", current->mean_general_skills);
	fputs(data, file);
	fputs("</mean_general_skills>\n", file);
		fputs("<mean_adaptation_speed>", file);
	sprintf(data, "%f", current->mean_adaptation_speed);
	fputs(data, file);
	fputs("</mean_adaptation_speed>\n", file);
		fputs("<productivity_progress_in_economy>", file);
	sprintf(data, "%f", current->productivity_progress_in_economy);
	fputs(data, file);
	fputs("</productivity_progress_in_economy>\n", file);
		fputs("<economy_wide_capital_stock>", file);
	sprintf(data, "%f", current->economy_wide_capital_stock);
	fputs(data, file);
	fputs("</economy_wide_capital_stock>\n", file);
		fputs("<list_adaptation_speed>", file);
	write_adt_list_adaptation_speed_dynamic_array(file, &current->list_adaptation_speed);
	fputs("</list_adaptation_speed>\n", file);
		fputs("<igfirm_balance_sheet_calendar>", file);
	write_igfirm_balance_sheet_adt(file, &current->igfirm_balance_sheet_calendar);
	fputs("</igfirm_balance_sheet_calendar>\n", file);
		fputs("<igfirm_stocks_calendar>", file);
	write_igfirm_stocks_adt(file, &current->igfirm_stocks_calendar);
	fputs("</igfirm_stocks_calendar>\n", file);
		fputs("<igfirm_outflows_calendar>", file);
	write_igfirm_outflows_adt(file, &current->igfirm_outflows_calendar);
	fputs("</igfirm_outflows_calendar>\n", file);
		fputs("<igfirm_inflows_calendar>", file);
	write_igfirm_inflows_adt(file, &current->igfirm_inflows_calendar);
	fputs("</igfirm_inflows_calendar>\n", file);
		fputs("<age>", file);
	sprintf(data, "%i", current->age);
	fputs(data, file);
	fputs("</age>\n", file);
		fputs("<transfer_payment>", file);
	sprintf(data, "%f", current->transfer_payment);
	fputs(data, file);
	fputs("</transfer_payment>\n", file);
		fputs("<subsidy_pct>", file);
	sprintf(data, "%f", current->subsidy_pct);
	fputs(data, file);
	fputs("</subsidy_pct>\n", file);
		fputs("<active>", file);
	sprintf(data, "%i", current->active);
	fputs(data, file);
	fputs("</active>\n", file);
		fputs("<bankruptcy_idle_counter>", file);
	sprintf(data, "%i", current->bankruptcy_idle_counter);
	fputs(data, file);
	fputs("</bankruptcy_idle_counter>\n", file);
		fputs("<bankruptcy_state>", file);
	sprintf(data, "%i", current->bankruptcy_state);
	fputs(data, file);
	fputs("</bankruptcy_state>\n", file);
		fputs("<bankruptcy_insolvency_state>", file);
	sprintf(data, "%i", current->bankruptcy_insolvency_state);
	fputs(data, file);
	fputs("</bankruptcy_insolvency_state>\n", file);
		fputs("<bankruptcy_illiquidity_state>", file);
	sprintf(data, "%i", current->bankruptcy_illiquidity_state);
	fputs(data, file);
	fputs("</bankruptcy_illiquidity_state>\n", file);
		fputs("<financial_crisis_state>", file);
	sprintf(data, "%i", current->financial_crisis_state);
	fputs(data, file);
	fputs("</financial_crisis_state>\n", file);
		fputs("<economy_wide_general_skills_in_firms>", file);
	sprintf(data, "%f", current->economy_wide_general_skills_in_firms);
	fputs(data, file);
	fputs("</economy_wide_general_skills_in_firms>\n", file);
		fputs("<economy_wide_specific_skills_in_firms>", file);
	sprintf(data, "%f", current->economy_wide_specific_skills_in_firms);
	fputs(data, file);
	fputs("</economy_wide_specific_skills_in_firms>\n", file);
		fputs("<subsidy_payment>", file);
	sprintf(data, "%f", current->subsidy_payment);
	fputs(data, file);
	fputs("</subsidy_payment>\n", file);
		fputs("<wage_offer>", file);
	sprintf(data, "%f", current->wage_offer);
	fputs(data, file);
	fputs("</wage_offer>\n", file);

	fputs("</xagent>\n", file);
}

void write_Eurostat_agent(FILE *file, xmachine_memory_Eurostat * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>Eurostat</name>\n", file);
		fputs("<id>", file);
	sprintf(data, "%i", current->id);
	fputs(data, file);
	fputs("</id>\n", file);

	fputs("</xagent>\n", file);
}

void write_Bank_agent(FILE *file, xmachine_memory_Bank * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>Bank</name>\n", file);
		fputs("<id>", file);
	sprintf(data, "%i", current->id);
	fputs(data, file);
	fputs("</id>\n", file);
		fputs("<region_id>", file);
	sprintf(data, "%i", current->region_id);
	fputs(data, file);
	fputs("</region_id>\n", file);
		fputs("<gov_id>", file);
	sprintf(data, "%i", current->gov_id);
	fputs(data, file);
	fputs("</gov_id>\n", file);
		fputs("<partition_id>", file);
	sprintf(data, "%i", current->partition_id);
	fputs(data, file);
	fputs("</partition_id>\n", file);
		fputs("<init_transient_period>", file);
	sprintf(data, "%i", current->init_transient_period);
	fputs(data, file);
	fputs("</init_transient_period>\n", file);
		fputs("<plan_sell_house>", file);
	sprintf(data, "%i", current->plan_sell_house);
	fputs(data, file);
	fputs("</plan_sell_house>\n", file);
		fputs("<lookuptable_riskweights_mortgages>", file);
	write_double_dynamic_array(file, &current->lookuptable_riskweights_mortgages);
	fputs("</lookuptable_riskweights_mortgages>\n", file);
		fputs("<basel_risk_weight>", file);
	sprintf(data, "%f", current->basel_risk_weight);
	fputs(data, file);
	fputs("</basel_risk_weight>\n", file);
		fputs("<firm_npl_daily>", file);
	write_double_dynamic_array(file, &current->firm_npl_daily);
	fputs("</firm_npl_daily>\n", file);
		fputs("<firm_ld_daily>", file);
	write_double_dynamic_array(file, &current->firm_ld_daily);
	fputs("</firm_ld_daily>\n", file);
		fputs("<firm_ll_daily>", file);
	write_double_dynamic_array(file, &current->firm_ll_daily);
	fputs("</firm_ll_daily>\n", file);
		fputs("<firm_pl_daily>", file);
	write_double_dynamic_array(file, &current->firm_pl_daily);
	fputs("</firm_pl_daily>\n", file);
		fputs("<firm_pd_qtr>", file);
	sprintf(data, "%f", current->firm_pd_qtr);
	fputs(data, file);
	fputs("</firm_pd_qtr>\n", file);
		fputs("<firm_pd_year>", file);
	sprintf(data, "%f", current->firm_pd_year);
	fputs(data, file);
	fputs("</firm_pd_year>\n", file);
		fputs("<firm_lgd_qtr>", file);
	sprintf(data, "%f", current->firm_lgd_qtr);
	fputs(data, file);
	fputs("</firm_lgd_qtr>\n", file);
		fputs("<firm_lgd_year>", file);
	sprintf(data, "%f", current->firm_lgd_year);
	fputs(data, file);
	fputs("</firm_lgd_year>\n", file);
		fputs("<firm_el_qtr>", file);
	sprintf(data, "%f", current->firm_el_qtr);
	fputs(data, file);
	fputs("</firm_el_qtr>\n", file);
		fputs("<firm_pd_cycle>", file);
	write_double_dynamic_array(file, &current->firm_pd_cycle);
	fputs("</firm_pd_cycle>\n", file);
		fputs("<firm_lgd_cycle>", file);
	write_double_dynamic_array(file, &current->firm_lgd_cycle);
	fputs("</firm_lgd_cycle>\n", file);
		fputs("<firm_pd_ttc>", file);
	sprintf(data, "%f", current->firm_pd_ttc);
	fputs(data, file);
	fputs("</firm_pd_ttc>\n", file);
		fputs("<firm_lgd_ttc>", file);
	sprintf(data, "%f", current->firm_lgd_ttc);
	fputs(data, file);
	fputs("</firm_lgd_ttc>\n", file);
		fputs("<hh_npl_daily>", file);
	write_double_dynamic_array(file, &current->hh_npl_daily);
	fputs("</hh_npl_daily>\n", file);
		fputs("<hh_ll_daily>", file);
	write_double_dynamic_array(file, &current->hh_ll_daily);
	fputs("</hh_ll_daily>\n", file);
		fputs("<hh_ld_daily>", file);
	write_double_dynamic_array(file, &current->hh_ld_daily);
	fputs("</hh_ld_daily>\n", file);
		fputs("<hh_pl_daily>", file);
	write_double_dynamic_array(file, &current->hh_pl_daily);
	fputs("</hh_pl_daily>\n", file);
		fputs("<hh_pd_qtr>", file);
	sprintf(data, "%f", current->hh_pd_qtr);
	fputs(data, file);
	fputs("</hh_pd_qtr>\n", file);
		fputs("<hh_pd_year>", file);
	sprintf(data, "%f", current->hh_pd_year);
	fputs(data, file);
	fputs("</hh_pd_year>\n", file);
		fputs("<hh_lgd_qtr>", file);
	sprintf(data, "%f", current->hh_lgd_qtr);
	fputs(data, file);
	fputs("</hh_lgd_qtr>\n", file);
		fputs("<hh_lgd_year>", file);
	sprintf(data, "%f", current->hh_lgd_year);
	fputs(data, file);
	fputs("</hh_lgd_year>\n", file);
		fputs("<hh_el_qtr>", file);
	sprintf(data, "%f", current->hh_el_qtr);
	fputs(data, file);
	fputs("</hh_el_qtr>\n", file);
		fputs("<hh_pd_cycle>", file);
	write_double_dynamic_array(file, &current->hh_pd_cycle);
	fputs("</hh_pd_cycle>\n", file);
		fputs("<hh_lgd_cycle>", file);
	write_double_dynamic_array(file, &current->hh_lgd_cycle);
	fputs("</hh_lgd_cycle>\n", file);
		fputs("<hh_pd_ttc>", file);
	sprintf(data, "%f", current->hh_pd_ttc);
	fputs(data, file);
	fputs("</hh_pd_ttc>\n", file);
		fputs("<hh_lgd_ttc>", file);
	sprintf(data, "%f", current->hh_lgd_ttc);
	fputs(data, file);
	fputs("</hh_lgd_ttc>\n", file);
		fputs("<active>", file);
	sprintf(data, "%i", current->active);
	fputs(data, file);
	fputs("</active>\n", file);
		fputs("<inactive>", file);
	sprintf(data, "%i", current->inactive);
	fputs(data, file);
	fputs("</inactive>\n", file);
		fputs("<cash>", file);
	sprintf(data, "%f", current->cash);
	fputs(data, file);
	fputs("</cash>\n", file);
		fputs("<reserves>", file);
	sprintf(data, "%f", current->reserves);
	fputs(data, file);
	fputs("</reserves>\n", file);
		fputs("<regulatory_reserves>", file);
	sprintf(data, "%f", current->regulatory_reserves);
	fputs(data, file);
	fputs("</regulatory_reserves>\n", file);
		fputs("<total_credit>", file);
	sprintf(data, "%f", current->total_credit);
	fputs(data, file);
	fputs("</total_credit>\n", file);
		fputs("<equity>", file);
	sprintf(data, "%f", current->equity);
	fputs(data, file);
	fputs("</equity>\n", file);
		fputs("<ecb_debt>", file);
	sprintf(data, "%f", current->ecb_debt);
	fputs(data, file);
	fputs("</ecb_debt>\n", file);
		fputs("<risk_exposure>", file);
	sprintf(data, "%f", current->risk_exposure);
	fputs(data, file);
	fputs("</risk_exposure>\n", file);
		fputs("<deposit_interest_rate>", file);
	sprintf(data, "%f", current->deposit_interest_rate);
	fputs(data, file);
	fputs("</deposit_interest_rate>\n", file);
		fputs("<bank_gamma>", file);
	write_double_static_array(file, current->bank_gamma, 2);
	fputs("</bank_gamma>\n", file);
		fputs("<profits>", file);
	write_double_static_array(file, current->profits, 2);
	fputs("</profits>\n", file);
		fputs("<bank_dividend_rate>", file);
	sprintf(data, "%f", current->bank_dividend_rate);
	fputs(data, file);
	fputs("</bank_dividend_rate>\n", file);
		fputs("<tax_rate_corporate>", file);
	sprintf(data, "%f", current->tax_rate_corporate);
	fputs(data, file);
	fputs("</tax_rate_corporate>\n", file);
		fputs("<current_shares_outstanding>", file);
	sprintf(data, "%i", current->current_shares_outstanding);
	fputs(data, file);
	fputs("</current_shares_outstanding>\n", file);
		fputs("<debt_period>", file);
	sprintf(data, "%f", current->debt_period);
	fputs(data, file);
	fputs("</debt_period>\n", file);
		fputs("<loan_request_message_found>", file);
	sprintf(data, "%i", current->loan_request_message_found);
	fputs(data, file);
	fputs("</loan_request_message_found>\n", file);
		fputs("<day_of_month_to_act>", file);
	sprintf(data, "%i", current->day_of_month_to_act);
	fputs(data, file);
	fputs("</day_of_month_to_act>\n", file);
		fputs("<deposits>", file);
	sprintf(data, "%f", current->deposits);
	fputs(data, file);
	fputs("</deposits>\n", file);
		fputs("<deposits_previous>", file);
	sprintf(data, "%f", current->deposits_previous);
	fputs(data, file);
	fputs("</deposits_previous>\n", file);
		fputs("<firm_loan_installments>", file);
	sprintf(data, "%f", current->firm_loan_installments);
	fputs(data, file);
	fputs("</firm_loan_installments>\n", file);
		fputs("<firm_loan_installments_in_calendar_month>", file);
	sprintf(data, "%f", current->firm_loan_installments_in_calendar_month);
	fputs(data, file);
	fputs("</firm_loan_installments_in_calendar_month>\n", file);
		fputs("<firm_interest_payments>", file);
	sprintf(data, "%f", current->firm_interest_payments);
	fputs(data, file);
	fputs("</firm_interest_payments>\n", file);
		fputs("<firm_interest_payments_in_calendar_month>", file);
	sprintf(data, "%f", current->firm_interest_payments_in_calendar_month);
	fputs(data, file);
	fputs("</firm_interest_payments_in_calendar_month>\n", file);
		fputs("<firm_loan_issues>", file);
	sprintf(data, "%f", current->firm_loan_issues);
	fputs(data, file);
	fputs("</firm_loan_issues>\n", file);
		fputs("<ecb_interest_payment>", file);
	sprintf(data, "%f", current->ecb_interest_payment);
	fputs(data, file);
	fputs("</ecb_interest_payment>\n", file);
		fputs("<total_dividend_payment>", file);
	sprintf(data, "%f", current->total_dividend_payment);
	fputs(data, file);
	fputs("</total_dividend_payment>\n", file);
		fputs("<total_dividends_in_calendar_month>", file);
	sprintf(data, "%f", current->total_dividends_in_calendar_month);
	fputs(data, file);
	fputs("</total_dividends_in_calendar_month>\n", file);
		fputs("<taxes>", file);
	sprintf(data, "%f", current->taxes);
	fputs(data, file);
	fputs("</taxes>\n", file);
		fputs("<dividend_per_share>", file);
	sprintf(data, "%f", current->dividend_per_share);
	fputs(data, file);
	fputs("</dividend_per_share>\n", file);
		fputs("<current_share_price>", file);
	sprintf(data, "%f", current->current_share_price);
	fputs(data, file);
	fputs("</current_share_price>\n", file);
		fputs("<leverage_ratio>", file);
	sprintf(data, "%f", current->leverage_ratio);
	fputs(data, file);
	fputs("</leverage_ratio>\n", file);
		fputs("<reserve_deposit_ratio>", file);
	sprintf(data, "%f", current->reserve_deposit_ratio);
	fputs(data, file);
	fputs("</reserve_deposit_ratio>\n", file);
		fputs("<equity_asset_ratio>", file);
	sprintf(data, "%f", current->equity_asset_ratio);
	fputs(data, file);
	fputs("</equity_asset_ratio>\n", file);
		fputs("<debt_equity_ratio>", file);
	sprintf(data, "%f", current->debt_equity_ratio);
	fputs(data, file);
	fputs("</debt_equity_ratio>\n", file);
		fputs("<mean_interest_rate>", file);
	sprintf(data, "%f", current->mean_interest_rate);
	fputs(data, file);
	fputs("</mean_interest_rate>\n", file);
		fputs("<sum_new_interest_rates_in_calendar_month>", file);
	sprintf(data, "%f", current->sum_new_interest_rates_in_calendar_month);
	fputs(data, file);
	fputs("</sum_new_interest_rates_in_calendar_month>\n", file);
		fputs("<no_new_loans_in_calendar_month>", file);
	sprintf(data, "%i", current->no_new_loans_in_calendar_month);
	fputs(data, file);
	fputs("</no_new_loans_in_calendar_month>\n", file);
		fputs("<paid_interest_daily>", file);
	sprintf(data, "%f", current->paid_interest_daily);
	fputs(data, file);
	fputs("</paid_interest_daily>\n", file);
		fputs("<paid_interest_in_calendar_month>", file);
	sprintf(data, "%f", current->paid_interest_in_calendar_month);
	fputs(data, file);
	fputs("</paid_interest_in_calendar_month>\n", file);
		fputs("<excess_risk_exposure>", file);
	sprintf(data, "%f", current->excess_risk_exposure);
	fputs(data, file);
	fputs("</excess_risk_exposure>\n", file);
		fputs("<excess_liquidity>", file);
	sprintf(data, "%f", current->excess_liquidity);
	fputs(data, file);
	fputs("</excess_liquidity>\n", file);
		fputs("<total_bad_debt_calendar_month>", file);
	sprintf(data, "%f", current->total_bad_debt_calendar_month);
	fputs(data, file);
	fputs("</total_bad_debt_calendar_month>\n", file);
		fputs("<proba_default_distribution>", file);
	write_double_dynamic_array(file, &current->proba_default_distribution);
	fputs("</proba_default_distribution>\n", file);
		fputs("<liquidity_coverage_ratio>", file);
	sprintf(data, "%f", current->liquidity_coverage_ratio);
	fputs(data, file);
	fputs("</liquidity_coverage_ratio>\n", file);
		fputs("<bank_balance_sheet_calendar>", file);
	write_bank_balance_sheet_adt(file, &current->bank_balance_sheet_calendar);
	fputs("</bank_balance_sheet_calendar>\n", file);
		fputs("<bank_stocks_calendar>", file);
	write_bank_stocks_adt(file, &current->bank_stocks_calendar);
	fputs("</bank_stocks_calendar>\n", file);
		fputs("<bank_outflows_calendar>", file);
	write_bank_outflows_adt(file, &current->bank_outflows_calendar);
	fputs("</bank_outflows_calendar>\n", file);
		fputs("<bank_inflows_calendar>", file);
	write_bank_inflows_adt(file, &current->bank_inflows_calendar);
	fputs("</bank_inflows_calendar>\n", file);
		fputs("<total_income>", file);
	sprintf(data, "%f", current->total_income);
	fputs(data, file);
	fputs("</total_income>\n", file);
		fputs("<total_expenses>", file);
	sprintf(data, "%f", current->total_expenses);
	fputs(data, file);
	fputs("</total_expenses>\n", file);
		fputs("<total_assets>", file);
	sprintf(data, "%f", current->total_assets);
	fputs(data, file);
	fputs("</total_assets>\n", file);
		fputs("<total_liabilities>", file);
	sprintf(data, "%f", current->total_liabilities);
	fputs(data, file);
	fputs("</total_liabilities>\n", file);
		fputs("<loan_loss_reserve_firm_loans>", file);
	sprintf(data, "%f", current->loan_loss_reserve_firm_loans);
	fputs(data, file);
	fputs("</loan_loss_reserve_firm_loans>\n", file);
		fputs("<loan_loss_reserve_mortgage_loans>", file);
	sprintf(data, "%f", current->loan_loss_reserve_mortgage_loans);
	fputs(data, file);
	fputs("</loan_loss_reserve_mortgage_loans>\n", file);
		fputs("<mortgage_portfolio>", file);
	write_mortgage_contract_adt_dynamic_array(file, &current->mortgage_portfolio);
	fputs("</mortgage_portfolio>\n", file);
		fputs("<bank_inflows_monthly_mortgage_payments>", file);
	sprintf(data, "%f", current->bank_inflows_monthly_mortgage_payments);
	fputs(data, file);
	fputs("</bank_inflows_monthly_mortgage_payments>\n", file);
		fputs("<bank_outflows_monthly_mortgage_issues>", file);
	sprintf(data, "%f", current->bank_outflows_monthly_mortgage_issues);
	fputs(data, file);
	fputs("</bank_outflows_monthly_mortgage_issues>\n", file);
		fputs("<no_monthly_new_mortgages_flow>", file);
	sprintf(data, "%i", current->no_monthly_new_mortgages_flow);
	fputs(data, file);
	fputs("</no_monthly_new_mortgages_flow>\n", file);
		fputs("<no_mortgages_outstanding>", file);
	sprintf(data, "%i", current->no_mortgages_outstanding);
	fputs(data, file);
	fputs("</no_mortgages_outstanding>\n", file);
		fputs("<seized_collateral>", file);
	write_foreclosure_adt_dynamic_array(file, &current->seized_collateral);
	fputs("</seized_collateral>\n", file);

	fputs("</xagent>\n", file);
}

void write_Government_agent(FILE *file, xmachine_memory_Government * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>Government</name>\n", file);
		fputs("<id>", file);
	sprintf(data, "%i", current->id);
	fputs(data, file);
	fputs("</id>\n", file);
		fputs("<list_of_regions>", file);
	write_int_dynamic_array(file, &current->list_of_regions);
	fputs("</list_of_regions>\n", file);
		fputs("<payment_account>", file);
	sprintf(data, "%f", current->payment_account);
	fputs(data, file);
	fputs("</payment_account>\n", file);
		fputs("<day_of_month_to_act>", file);
	sprintf(data, "%i", current->day_of_month_to_act);
	fputs(data, file);
	fputs("</day_of_month_to_act>\n", file);
		fputs("<region_id>", file);
	sprintf(data, "%i", current->region_id);
	fputs(data, file);
	fputs("</region_id>\n", file);
		fputs("<partition_id>", file);
	sprintf(data, "%i", current->partition_id);
	fputs(data, file);
	fputs("</partition_id>\n", file);
		fputs("<init_transient_period>", file);
	sprintf(data, "%i", current->init_transient_period);
	fputs(data, file);
	fputs("</init_transient_period>\n", file);
		fputs("<unemployment_benefit_pct>", file);
	sprintf(data, "%f", current->unemployment_benefit_pct);
	fputs(data, file);
	fputs("</unemployment_benefit_pct>\n", file);
		fputs("<gdp_fraction_consumption>", file);
	sprintf(data, "%f", current->gdp_fraction_consumption);
	fputs(data, file);
	fputs("</gdp_fraction_consumption>\n", file);
		fputs("<gdp_fraction_investment>", file);
	sprintf(data, "%f", current->gdp_fraction_investment);
	fputs(data, file);
	fputs("</gdp_fraction_investment>\n", file);
		fputs("<tax_rate_corporate>", file);
	sprintf(data, "%f", current->tax_rate_corporate);
	fputs(data, file);
	fputs("</tax_rate_corporate>\n", file);
		fputs("<tax_rate_hh_labour>", file);
	sprintf(data, "%f", current->tax_rate_hh_labour);
	fputs(data, file);
	fputs("</tax_rate_hh_labour>\n", file);
		fputs("<tax_rate_hh_capital>", file);
	sprintf(data, "%f", current->tax_rate_hh_capital);
	fputs(data, file);
	fputs("</tax_rate_hh_capital>\n", file);
		fputs("<tax_rate_vat>", file);
	sprintf(data, "%f", current->tax_rate_vat);
	fputs(data, file);
	fputs("</tax_rate_vat>\n", file);
		fputs("<monthly_tax_revenues>", file);
	sprintf(data, "%f", current->monthly_tax_revenues);
	fputs(data, file);
	fputs("</monthly_tax_revenues>\n", file);
		fputs("<yearly_tax_revenues>", file);
	sprintf(data, "%f", current->yearly_tax_revenues);
	fputs(data, file);
	fputs("</yearly_tax_revenues>\n", file);
		fputs("<monthly_benefit_payment>", file);
	sprintf(data, "%f", current->monthly_benefit_payment);
	fputs(data, file);
	fputs("</monthly_benefit_payment>\n", file);
		fputs("<yearly_benefit_payment>", file);
	sprintf(data, "%f", current->yearly_benefit_payment);
	fputs(data, file);
	fputs("</yearly_benefit_payment>\n", file);
		fputs("<hh_transfer_payment>", file);
	sprintf(data, "%f", current->hh_transfer_payment);
	fputs(data, file);
	fputs("</hh_transfer_payment>\n", file);
		fputs("<firm_transfer_payment>", file);
	sprintf(data, "%f", current->firm_transfer_payment);
	fputs(data, file);
	fputs("</firm_transfer_payment>\n", file);
		fputs("<monthly_transfer_payment>", file);
	sprintf(data, "%f", current->monthly_transfer_payment);
	fputs(data, file);
	fputs("</monthly_transfer_payment>\n", file);
		fputs("<yearly_transfer_payment>", file);
	sprintf(data, "%f", current->yearly_transfer_payment);
	fputs(data, file);
	fputs("</yearly_transfer_payment>\n", file);
		fputs("<hh_subsidy_pct>", file);
	sprintf(data, "%f", current->hh_subsidy_pct);
	fputs(data, file);
	fputs("</hh_subsidy_pct>\n", file);
		fputs("<firm_subsidy_pct>", file);
	sprintf(data, "%f", current->firm_subsidy_pct);
	fputs(data, file);
	fputs("</firm_subsidy_pct>\n", file);
		fputs("<regional_firm_subsidy>", file);
	sprintf(data, "%i", current->regional_firm_subsidy);
	fputs(data, file);
	fputs("</regional_firm_subsidy>\n", file);
		fputs("<subsidy_flag>", file);
	sprintf(data, "%i", current->subsidy_flag);
	fputs(data, file);
	fputs("</subsidy_flag>\n", file);
		fputs("<gov_interest_rate>", file);
	sprintf(data, "%f", current->gov_interest_rate);
	fputs(data, file);
	fputs("</gov_interest_rate>\n", file);
		fputs("<monthly_bond_interest_payment>", file);
	sprintf(data, "%f", current->monthly_bond_interest_payment);
	fputs(data, file);
	fputs("</monthly_bond_interest_payment>\n", file);
		fputs("<monthly_subsidy_payment>", file);
	sprintf(data, "%f", current->monthly_subsidy_payment);
	fputs(data, file);
	fputs("</monthly_subsidy_payment>\n", file);
		fputs("<monthly_consumption_expenditure>", file);
	sprintf(data, "%f", current->monthly_consumption_expenditure);
	fputs(data, file);
	fputs("</monthly_consumption_expenditure>\n", file);
		fputs("<monthly_investment_expenditure>", file);
	sprintf(data, "%f", current->monthly_investment_expenditure);
	fputs(data, file);
	fputs("</monthly_investment_expenditure>\n", file);
		fputs("<monthly_budget_balance>", file);
	sprintf(data, "%f", current->monthly_budget_balance);
	fputs(data, file);
	fputs("</monthly_budget_balance>\n", file);
		fputs("<monthly_gdp>", file);
	sprintf(data, "%f", current->monthly_gdp);
	fputs(data, file);
	fputs("</monthly_gdp>\n", file);
		fputs("<monthly_budget_balance_gdp_fraction>", file);
	sprintf(data, "%f", current->monthly_budget_balance_gdp_fraction);
	fputs(data, file);
	fputs("</monthly_budget_balance_gdp_fraction>\n", file);
		fputs("<monthly_consumption_budget>", file);
	sprintf(data, "%f", current->monthly_consumption_budget);
	fputs(data, file);
	fputs("</monthly_consumption_budget>\n", file);
		fputs("<monthly_investment_budget>", file);
	sprintf(data, "%f", current->monthly_investment_budget);
	fputs(data, file);
	fputs("</monthly_investment_budget>\n", file);
		fputs("<monthly_income>", file);
	sprintf(data, "%f", current->monthly_income);
	fputs(data, file);
	fputs("</monthly_income>\n", file);
		fputs("<monthly_expenditure>", file);
	sprintf(data, "%f", current->monthly_expenditure);
	fputs(data, file);
	fputs("</monthly_expenditure>\n", file);
		fputs("<yearly_subsidy_payment>", file);
	sprintf(data, "%f", current->yearly_subsidy_payment);
	fputs(data, file);
	fputs("</yearly_subsidy_payment>\n", file);
		fputs("<yearly_bond_interest_payment>", file);
	sprintf(data, "%f", current->yearly_bond_interest_payment);
	fputs(data, file);
	fputs("</yearly_bond_interest_payment>\n", file);
		fputs("<yearly_investment_expenditure>", file);
	sprintf(data, "%f", current->yearly_investment_expenditure);
	fputs(data, file);
	fputs("</yearly_investment_expenditure>\n", file);
		fputs("<yearly_consumption_expenditure>", file);
	sprintf(data, "%f", current->yearly_consumption_expenditure);
	fputs(data, file);
	fputs("</yearly_consumption_expenditure>\n", file);
		fputs("<yearly_income>", file);
	sprintf(data, "%f", current->yearly_income);
	fputs(data, file);
	fputs("</yearly_income>\n", file);
		fputs("<yearly_expenditure>", file);
	sprintf(data, "%f", current->yearly_expenditure);
	fputs(data, file);
	fputs("</yearly_expenditure>\n", file);
		fputs("<total_debt>", file);
	sprintf(data, "%f", current->total_debt);
	fputs(data, file);
	fputs("</total_debt>\n", file);
		fputs("<yearly_budget_balance>", file);
	sprintf(data, "%f", current->yearly_budget_balance);
	fputs(data, file);
	fputs("</yearly_budget_balance>\n", file);
		fputs("<total_money_financing>", file);
	sprintf(data, "%f", current->total_money_financing);
	fputs(data, file);
	fputs("</total_money_financing>\n", file);
		fputs("<total_bond_financing>", file);
	sprintf(data, "%f", current->total_bond_financing);
	fputs(data, file);
	fputs("</total_bond_financing>\n", file);
		fputs("<country_wide_mean_wage>", file);
	sprintf(data, "%f", current->country_wide_mean_wage);
	fputs(data, file);
	fputs("</country_wide_mean_wage>\n", file);
		fputs("<num_unemployed>", file);
	sprintf(data, "%i", current->num_unemployed);
	fputs(data, file);
	fputs("</num_unemployed>\n", file);
		fputs("<yearly_gdp>", file);
	sprintf(data, "%f", current->yearly_gdp);
	fputs(data, file);
	fputs("</yearly_gdp>\n", file);
		fputs("<previous_year_gdp>", file);
	sprintf(data, "%f", current->previous_year_gdp);
	fputs(data, file);
	fputs("</previous_year_gdp>\n", file);
		fputs("<gdp_growth>", file);
	sprintf(data, "%f", current->gdp_growth);
	fputs(data, file);
	fputs("</gdp_growth>\n", file);
		fputs("<gdp_forecast>", file);
	sprintf(data, "%f", current->gdp_forecast);
	fputs(data, file);
	fputs("</gdp_forecast>\n", file);
		fputs("<yearly_income_forecast>", file);
	sprintf(data, "%f", current->yearly_income_forecast);
	fputs(data, file);
	fputs("</yearly_income_forecast>\n", file);
		fputs("<yearly_expenditure_budget>", file);
	sprintf(data, "%f", current->yearly_expenditure_budget);
	fputs(data, file);
	fputs("</yearly_expenditure_budget>\n", file);
		fputs("<budget_balance_forecast>", file);
	sprintf(data, "%f", current->budget_balance_forecast);
	fputs(data, file);
	fputs("</budget_balance_forecast>\n", file);
		fputs("<yearly_consumption_budget>", file);
	sprintf(data, "%f", current->yearly_consumption_budget);
	fputs(data, file);
	fputs("</yearly_consumption_budget>\n", file);
		fputs("<yearly_investment_budget>", file);
	sprintf(data, "%f", current->yearly_investment_budget);
	fputs(data, file);
	fputs("</yearly_investment_budget>\n", file);
		fputs("<yearly_budget_balance_gdp_fraction>", file);
	sprintf(data, "%f", current->yearly_budget_balance_gdp_fraction);
	fputs(data, file);
	fputs("</yearly_budget_balance_gdp_fraction>\n", file);
		fputs("<total_assets>", file);
	sprintf(data, "%f", current->total_assets);
	fputs(data, file);
	fputs("</total_assets>\n", file);
		fputs("<total_liabilities>", file);
	sprintf(data, "%f", current->total_liabilities);
	fputs(data, file);
	fputs("</total_liabilities>\n", file);
		fputs("<cumulated_deficit>", file);
	sprintf(data, "%f", current->cumulated_deficit);
	fputs(data, file);
	fputs("</cumulated_deficit>\n", file);
		fputs("<inflation_rate>", file);
	sprintf(data, "%f", current->inflation_rate);
	fputs(data, file);
	fputs("</inflation_rate>\n", file);
		fputs("<unemployment_rate>", file);
	sprintf(data, "%f", current->unemployment_rate);
	fputs(data, file);
	fputs("</unemployment_rate>\n", file);
		fputs("<human_capital_policy_installation_date_in_years>", file);
	sprintf(data, "%i", current->human_capital_policy_installation_date_in_years);
	fputs(data, file);
	fputs("</human_capital_policy_installation_date_in_years>\n", file);
		fputs("<human_capital_policy_flag>", file);
	sprintf(data, "%i", current->human_capital_policy_flag);
	fputs(data, file);
	fputs("</human_capital_policy_flag>\n", file);
		fputs("<new_skill_distribution>", file);
	write_adt_skill_distribution_dynamic_array(file, &current->new_skill_distribution);
	fputs("</new_skill_distribution>\n", file);
		fputs("<gov_balance_sheet_calendar>", file);
	write_gov_balance_sheet_adt(file, &current->gov_balance_sheet_calendar);
	fputs("</gov_balance_sheet_calendar>\n", file);
		fputs("<gov_stocks_calendar>", file);
	write_gov_stocks_adt(file, &current->gov_stocks_calendar);
	fputs("</gov_stocks_calendar>\n", file);
		fputs("<gov_outflows_calendar>", file);
	write_gov_outflows_adt(file, &current->gov_outflows_calendar);
	fputs("</gov_outflows_calendar>\n", file);
		fputs("<gov_inflows_calendar>", file);
	write_gov_inflows_adt(file, &current->gov_inflows_calendar);
	fputs("</gov_inflows_calendar>\n", file);

	fputs("</xagent>\n", file);
}

void write_CentralBank_agent(FILE *file, xmachine_memory_CentralBank * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>CentralBank</name>\n", file);
		fputs("<id>", file);
	sprintf(data, "%i", current->id);
	fputs(data, file);
	fputs("</id>\n", file);
		fputs("<region_id>", file);
	sprintf(data, "%i", current->region_id);
	fputs(data, file);
	fputs("</region_id>\n", file);
		fputs("<partition_id>", file);
	sprintf(data, "%i", current->partition_id);
	fputs(data, file);
	fputs("</partition_id>\n", file);
		fputs("<init_transient_period>", file);
	sprintf(data, "%i", current->init_transient_period);
	fputs(data, file);
	fputs("</init_transient_period>\n", file);
		fputs("<equity>", file);
	sprintf(data, "%f", current->equity);
	fputs(data, file);
	fputs("</equity>\n", file);
		fputs("<dividend_payment>", file);
	sprintf(data, "%f", current->dividend_payment);
	fputs(data, file);
	fputs("</dividend_payment>\n", file);
		fputs("<fiat_money>", file);
	sprintf(data, "%f", current->fiat_money);
	fputs(data, file);
	fputs("</fiat_money>\n", file);
		fputs("<fiat_money_banks>", file);
	sprintf(data, "%f", current->fiat_money_banks);
	fputs(data, file);
	fputs("</fiat_money_banks>\n", file);
		fputs("<fiat_money_firms>", file);
	sprintf(data, "%f", current->fiat_money_firms);
	fputs(data, file);
	fputs("</fiat_money_firms>\n", file);
		fputs("<ecb_deposits>", file);
	sprintf(data, "%f", current->ecb_deposits);
	fputs(data, file);
	fputs("</ecb_deposits>\n", file);
		fputs("<accounts_banks>", file);
	write_account_item_dynamic_array(file, &current->accounts_banks);
	fputs("</accounts_banks>\n", file);
		fputs("<accounts_govs>", file);
	write_account_item_dynamic_array(file, &current->accounts_govs);
	fputs("</accounts_govs>\n", file);
		fputs("<cash>", file);
	sprintf(data, "%f", current->cash);
	fputs(data, file);
	fputs("</cash>\n", file);
		fputs("<ecb_balance_sheet_calendar>", file);
	write_ecb_balance_sheet_adt(file, &current->ecb_balance_sheet_calendar);
	fputs("</ecb_balance_sheet_calendar>\n", file);
		fputs("<ecb_stocks_calendar>", file);
	write_ecb_stocks_adt(file, &current->ecb_stocks_calendar);
	fputs("</ecb_stocks_calendar>\n", file);
		fputs("<ecb_outflows_calendar>", file);
	write_ecb_outflows_adt(file, &current->ecb_outflows_calendar);
	fputs("</ecb_outflows_calendar>\n", file);
		fputs("<ecb_inflows_calendar>", file);
	write_ecb_inflows_adt(file, &current->ecb_inflows_calendar);
	fputs("</ecb_inflows_calendar>\n", file);
		fputs("<bond_holdings_value>", file);
	sprintf(data, "%f", current->bond_holdings_value);
	fputs(data, file);
	fputs("</bond_holdings_value>\n", file);
		fputs("<nr_gov_bonds>", file);
	sprintf(data, "%i", current->nr_gov_bonds);
	fputs(data, file);
	fputs("</nr_gov_bonds>\n", file);
		fputs("<fiat_money_govs>", file);
	sprintf(data, "%f", current->fiat_money_govs);
	fputs(data, file);
	fputs("</fiat_money_govs>\n", file);
		fputs("<fiat_money_bond_govs>", file);
	sprintf(data, "%f", current->fiat_money_bond_govs);
	fputs(data, file);
	fputs("</fiat_money_bond_govs>\n", file);
		fputs("<bank_interest>", file);
	sprintf(data, "%f", current->bank_interest);
	fputs(data, file);
	fputs("</bank_interest>\n", file);
		fputs("<gov_interest>", file);
	sprintf(data, "%f", current->gov_interest);
	fputs(data, file);
	fputs("</gov_interest>\n", file);
		fputs("<gov_bond_purchase>", file);
	sprintf(data, "%f", current->gov_bond_purchase);
	fputs(data, file);
	fputs("</gov_bond_purchase>\n", file);
		fputs("<total_income>", file);
	sprintf(data, "%f", current->total_income);
	fputs(data, file);
	fputs("</total_income>\n", file);
		fputs("<total_expenses>", file);
	sprintf(data, "%f", current->total_expenses);
	fputs(data, file);
	fputs("</total_expenses>\n", file);
		fputs("<total_assets>", file);
	sprintf(data, "%f", current->total_assets);
	fputs(data, file);
	fputs("</total_assets>\n", file);
		fputs("<total_liabilities>", file);
	sprintf(data, "%f", current->total_liabilities);
	fputs(data, file);
	fputs("</total_liabilities>\n", file);

	fputs("</xagent>\n", file);
}

void write_ClearingHouse_agent(FILE *file, xmachine_memory_ClearingHouse * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>ClearingHouse</name>\n", file);
		fputs("<id>", file);
	sprintf(data, "%i", current->id);
	fputs(data, file);
	fputs("</id>\n", file);
		fputs("<region_id>", file);
	sprintf(data, "%i", current->region_id);
	fputs(data, file);
	fputs("</region_id>\n", file);
		fputs("<partition_id>", file);
	sprintf(data, "%i", current->partition_id);
	fputs(data, file);
	fputs("</partition_id>\n", file);
		fputs("<init_transient_period>", file);
	sprintf(data, "%i", current->init_transient_period);
	fputs(data, file);
	fputs("</init_transient_period>\n", file);
		fputs("<pending_orders>", file);
	write_order_dynamic_array(file, &current->pending_orders);
	fputs("</pending_orders>\n", file);
		fputs("<processed_orders>", file);
	write_order_dynamic_array(file, &current->processed_orders);
	fputs("</processed_orders>\n", file);
		fputs("<stock_index>", file);
	write_index_adt(file, &current->stock_index);
	fputs("</stock_index>\n", file);
		fputs("<dsratio>", file);
	sprintf(data, "%f", current->dsratio);
	fputs(data, file);
	fputs("</dsratio>\n", file);
		fputs("<random_numbers_normal>", file);
	write_double_dynamic_array(file, &current->random_numbers_normal);
	fputs("</random_numbers_normal>\n", file);
		fputs("<monthly_counter_total_dividend>", file);
	sprintf(data, "%f", current->monthly_counter_total_dividend);
	fputs(data, file);
	fputs("</monthly_counter_total_dividend>\n", file);
		fputs("<stock_index_price>", file);
	sprintf(data, "%f", current->stock_index_price);
	fputs(data, file);
	fputs("</stock_index_price>\n", file);
		fputs("<house_auction>", file);
	write_auction_adt(file, &current->house_auction);
	fputs("</house_auction>\n", file);
		fputs("<rental_auction>", file);
	write_auction_adt(file, &current->rental_auction);
	fputs("</rental_auction>\n", file);
		fputs("<init_tenants>", file);
	write_tenant_adt_dynamic_array(file, &current->init_tenants);
	fputs("</init_tenants>\n", file);
		fputs("<init_landlords>", file);
	write_int_dynamic_array(file, &current->init_landlords);
	fputs("</init_landlords>\n", file);
		fputs("<init_owners>", file);
	write_int_dynamic_array(file, &current->init_owners);
	fputs("</init_owners>\n", file);

	fputs("</xagent>\n", file);
}

void write_NSA_agent(FILE *file, xmachine_memory_NSA * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>NSA</name>\n", file);
		fputs("<id>", file);
	sprintf(data, "%i", current->id);
	fputs(data, file);
	fputs("</id>\n", file);
		fputs("<region_id>", file);
	sprintf(data, "%i", current->region_id);
	fputs(data, file);
	fputs("</region_id>\n", file);
		fputs("<partition_id>", file);
	sprintf(data, "%i", current->partition_id);
	fputs(data, file);
	fputs("</partition_id>\n", file);
		fputs("<init_transient_period>", file);
	sprintf(data, "%i", current->init_transient_period);
	fputs(data, file);
	fputs("</init_transient_period>\n", file);
		fputs("<network_banks>", file);
	write_node_adt_dynamic_array(file, &current->network_banks);
	fputs("</network_banks>\n", file);
		fputs("<network_firms>", file);
	write_node_adt_dynamic_array(file, &current->network_firms);
	fputs("</network_firms>\n", file);
		fputs("<network_hhs>", file);
	write_node_adt_dynamic_array(file, &current->network_hhs);
	fputs("</network_hhs>\n", file);
		fputs("<network>", file);
	write_node_adt_dynamic_array(file, &current->network);
	fputs("</network>\n", file);
		fputs("<total_no_loans_banks>", file);
	sprintf(data, "%i", current->total_no_loans_banks);
	fputs(data, file);
	fputs("</total_no_loans_banks>\n", file);
		fputs("<total_no_loans_firms>", file);
	sprintf(data, "%i", current->total_no_loans_firms);
	fputs(data, file);
	fputs("</total_no_loans_firms>\n", file);
		fputs("<total_no_loans_hh>", file);
	sprintf(data, "%i", current->total_no_loans_hh);
	fputs(data, file);
	fputs("</total_no_loans_hh>\n", file);
		fputs("<total_value_loans_banks>", file);
	sprintf(data, "%f", current->total_value_loans_banks);
	fputs(data, file);
	fputs("</total_value_loans_banks>\n", file);
		fputs("<total_value_loans_firms>", file);
	sprintf(data, "%f", current->total_value_loans_firms);
	fputs(data, file);
	fputs("</total_value_loans_firms>\n", file);
		fputs("<total_value_loans_hh>", file);
	sprintf(data, "%f", current->total_value_loans_hh);
	fputs(data, file);
	fputs("</total_value_loans_hh>\n", file);
		fputs("<firm_loan_no_dist>", file);
	write_int_dynamic_array(file, &current->firm_loan_no_dist);
	fputs("</firm_loan_no_dist>\n", file);
		fputs("<firm_loan_value_dist>", file);
	write_double_dynamic_array(file, &current->firm_loan_value_dist);
	fputs("</firm_loan_value_dist>\n", file);
		fputs("<clustering_coefficient>", file);
	sprintf(data, "%f", current->clustering_coefficient);
	fputs(data, file);
	fputs("</clustering_coefficient>\n", file);
		fputs("<homophily_index>", file);
	sprintf(data, "%f", current->homophily_index);
	fputs(data, file);
	fputs("</homophily_index>\n", file);
		fputs("<average_path_length>", file);
	sprintf(data, "%f", current->average_path_length);
	fputs(data, file);
	fputs("</average_path_length>\n", file);
		fputs("<links>", file);
	sprintf(data, "%i", current->links);
	fputs(data, file);
	fputs("</links>\n", file);

	fputs("</xagent>\n", file);
}


void FLAME_write_xml(char * location, int iteration_number, int * output_types, int output_type_size)
{
	/* Pointer to file */
	FILE *file;
	char data[1000];
	
		sprintf(data, "%s%i.xml", location, iteration_number);
	
	if((file = fopen(data, "w"))==NULL)
	{
		printf("Error: cannot open file '%s' for writing\n", data);
		exit(0);
	}
	
	
	fputs("<states>\n", file);
	if(FLAME_integer_in_array(0, output_types, output_type_size))
	{
		fputs("<itno>", file);
		sprintf(data, "%i", iteration_number);
		fputs(data, file);
		fputs("</itno>\n", file);
		fputs("<environment>\n" , file);
			fputs("<rnd_seed>", file);
		sprintf(data, "%i", FLAME_environment_variable_rnd_seed);
		fputs(data, file);
		fputs("</rnd_seed>\n", file);
			fputs("<GSL_RNG_SEED>", file);
		sprintf(data, "%f", FLAME_environment_variable_GSL_RNG_SEED);
		fputs(data, file);
		fputs("</GSL_RNG_SEED>\n", file);
			fputs("<total_regions>", file);
		sprintf(data, "%i", FLAME_environment_variable_total_regions);
		fputs(data, file);
		fputs("</total_regions>\n", file);
			fputs("<id_debug_probe>", file);
		sprintf(data, "%i", FLAME_environment_variable_id_debug_probe);
		fputs(data, file);
		fputs("</id_debug_probe>\n", file);
			fputs("<print_debug_id_probe>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_id_probe);
		fputs(data, file);
		fputs("</print_debug_id_probe>\n", file);
			fputs("<time_debug_probe>", file);
		sprintf(data, "%i", FLAME_environment_variable_time_debug_probe);
		fputs(data, file);
		fputs("</time_debug_probe>\n", file);
			fputs("<print_log>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_log);
		fputs(data, file);
		fputs("</print_log>\n", file);
			fputs("<print_debug_bankruptcy>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_bankruptcy);
		fputs(data, file);
		fputs("</print_debug_bankruptcy>\n", file);
			fputs("<print_debug_eurostat>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_eurostat);
		fputs(data, file);
		fputs("</print_debug_eurostat>\n", file);
			fputs("<print_debug_ch>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_ch);
		fputs(data, file);
		fputs("</print_debug_ch>\n", file);
			fputs("<print_debug_afm>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_afm);
		fputs(data, file);
		fputs("</print_debug_afm>\n", file);
			fputs("<print_debug_afm_ch>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_afm_ch);
		fputs(data, file);
		fputs("</print_debug_afm_ch>\n", file);
			fputs("<print_debug_exp1>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_exp1);
		fputs(data, file);
		fputs("</print_debug_exp1>\n", file);
			fputs("<print_debug_file_exp1>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_file_exp1);
		fputs(data, file);
		fputs("</print_debug_file_exp1>\n", file);
			fputs("<print_debug_file_exp2>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_file_exp2);
		fputs(data, file);
		fputs("</print_debug_file_exp2>\n", file);
			fputs("<policy_exp1>", file);
		sprintf(data, "%i", FLAME_environment_variable_policy_exp1);
		fputs(data, file);
		fputs("</policy_exp1>\n", file);
			fputs("<print_debug_gov>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_gov);
		fputs(data, file);
		fputs("</print_debug_gov>\n", file);
			fputs("<print_debug_household>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_household);
		fputs(data, file);
		fputs("</print_debug_household>\n", file);
			fputs("<print_debug_credit>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_credit);
		fputs(data, file);
		fputs("</print_debug_credit>\n", file);
			fputs("<print_debug_nsa>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_nsa);
		fputs(data, file);
		fputs("</print_debug_nsa>\n", file);
			fputs("<print_debug_consumption>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_consumption);
		fputs(data, file);
		fputs("</print_debug_consumption>\n", file);
			fputs("<print_debug_finman>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_finman);
		fputs(data, file);
		fputs("</print_debug_finman>\n", file);
			fputs("<print_debug_production>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_production);
		fputs(data, file);
		fputs("</print_debug_production>\n", file);
			fputs("<print_debug_mall>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_mall);
		fputs(data, file);
		fputs("</print_debug_mall>\n", file);
			fputs("<print_debug>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug);
		fputs(data, file);
		fputs("</print_debug>\n", file);
			fputs("<print_debug_market_research>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_market_research);
		fputs(data, file);
		fputs("</print_debug_market_research>\n", file);
			fputs("<print_debug_credit_risk_mngt>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_credit_risk_mngt);
		fputs(data, file);
		fputs("</print_debug_credit_risk_mngt>\n", file);
			fputs("<print_debug_credit_unittest>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_credit_unittest);
		fputs(data, file);
		fputs("</print_debug_credit_unittest>\n", file);
			fputs("<print_debug_housing>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_housing);
		fputs(data, file);
		fputs("</print_debug_housing>\n", file);
			fputs("<print_debug_housing_unittest>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_housing_unittest);
		fputs(data, file);
		fputs("</print_debug_housing_unittest>\n", file);
			fputs("<print_debug_rental>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_rental);
		fputs(data, file);
		fputs("</print_debug_rental>\n", file);
			fputs("<print_debug_rental_unittest>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_rental_unittest);
		fputs(data, file);
		fputs("</print_debug_rental_unittest>\n", file);
			fputs("<switch_behavioral_state_transitions_housing>", file);
		sprintf(data, "%i", FLAME_environment_variable_switch_behavioral_state_transitions_housing);
		fputs(data, file);
		fputs("</switch_behavioral_state_transitions_housing>\n", file);
			fputs("<print_debug_mortgage>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_mortgage);
		fputs(data, file);
		fputs("</print_debug_mortgage>\n", file);
			fputs("<print_debug_mortgage_hh>", file);
		sprintf(data, "%i", FLAME_environment_variable_print_debug_mortgage_hh);
		fputs(data, file);
		fputs("</print_debug_mortgage_hh>\n", file);
			fputs("<policy_exp_energy_shock>", file);
		sprintf(data, "%i", FLAME_environment_variable_policy_exp_energy_shock);
		fputs(data, file);
		fputs("</policy_exp_energy_shock>\n", file);
			fputs("<policy_exp_stabilization_subsidy>", file);
		sprintf(data, "%i", FLAME_environment_variable_policy_exp_stabilization_subsidy);
		fputs(data, file);
		fputs("</policy_exp_stabilization_subsidy>\n", file);
			fputs("<policy_exp_stabilization_tax>", file);
		sprintf(data, "%i", FLAME_environment_variable_policy_exp_stabilization_tax);
		fputs(data, file);
		fputs("</policy_exp_stabilization_tax>\n", file);
			fputs("<const_bankruptcy_idle_period>", file);
		sprintf(data, "%i", FLAME_environment_variable_const_bankruptcy_idle_period);
		fputs(data, file);
		fputs("</const_bankruptcy_idle_period>\n", file);
			fputs("<days_per_month>", file);
		sprintf(data, "%i", FLAME_environment_variable_days_per_month);
		fputs(data, file);
		fputs("</days_per_month>\n", file);
			fputs("<xml_cloned>", file);
		sprintf(data, "%i", FLAME_environment_variable_xml_cloned);
		fputs(data, file);
		fputs("</xml_cloned>\n", file);
			fputs("<transition_phase_innov>", file);
		sprintf(data, "%i", FLAME_environment_variable_transition_phase_innov);
		fputs(data, file);
		fputs("</transition_phase_innov>\n", file);
			fputs("<transition_phase_recap>", file);
		sprintf(data, "%i", FLAME_environment_variable_transition_phase_recap);
		fputs(data, file);
		fputs("</transition_phase_recap>\n", file);
			fputs("<const_init_transient_period>", file);
		sprintf(data, "%i", FLAME_environment_variable_const_init_transient_period);
		fputs(data, file);
		fputs("</const_init_transient_period>\n", file);
			fputs("<individual_learning>", file);
		sprintf(data, "%i", FLAME_environment_variable_individual_learning);
		fputs(data, file);
		fputs("</individual_learning>\n", file);
			fputs("<const_wage_wealth_ratio>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_wage_wealth_ratio);
		fputs(data, file);
		fputs("</const_wage_wealth_ratio>\n", file);
			fputs("<const_income_tax_rate>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_income_tax_rate);
		fputs(data, file);
		fputs("</const_income_tax_rate>\n", file);
			fputs("<gamma_const>", file);
		sprintf(data, "%f", FLAME_environment_variable_gamma_const);
		fputs(data, file);
		fputs("</gamma_const>\n", file);
			fputs("<gamma_quality>", file);
		sprintf(data, "%f", FLAME_environment_variable_gamma_quality);
		fputs(data, file);
		fputs("</gamma_quality>\n", file);
			fputs("<depreciation_rate>", file);
		sprintf(data, "%f", FLAME_environment_variable_depreciation_rate);
		fputs(data, file);
		fputs("</depreciation_rate>\n", file);
			fputs("<discont_rate>", file);
		sprintf(data, "%f", FLAME_environment_variable_discont_rate);
		fputs(data, file);
		fputs("</discont_rate>\n", file);
			fputs("<mark_up>", file);
		sprintf(data, "%f", FLAME_environment_variable_mark_up);
		fputs(data, file);
		fputs("</mark_up>\n", file);
			fputs("<lambda>", file);
		sprintf(data, "%f", FLAME_environment_variable_lambda);
		fputs(data, file);
		fputs("</lambda>\n", file);
			fputs("<target_savings_rate>", file);
		sprintf(data, "%f", FLAME_environment_variable_target_savings_rate);
		fputs(data, file);
		fputs("</target_savings_rate>\n", file);
			fputs("<carrol_consumption_parameter>", file);
		sprintf(data, "%f", FLAME_environment_variable_carrol_consumption_parameter);
		fputs(data, file);
		fputs("</carrol_consumption_parameter>\n", file);
			fputs("<quantil_normal_distribution>", file);
		sprintf(data, "%f", FLAME_environment_variable_quantil_normal_distribution);
		fputs(data, file);
		fputs("</quantil_normal_distribution>\n", file);
			fputs("<firm_planning_horizon>", file);
		sprintf(data, "%i", FLAME_environment_variable_firm_planning_horizon);
		fputs(data, file);
		fputs("</firm_planning_horizon>\n", file);
			fputs("<adaption_delivery_volume>", file);
		sprintf(data, "%f", FLAME_environment_variable_adaption_delivery_volume);
		fputs(data, file);
		fputs("</adaption_delivery_volume>\n", file);
			fputs("<inv_inertia>", file);
		sprintf(data, "%f", FLAME_environment_variable_inv_inertia);
		fputs(data, file);
		fputs("</inv_inertia>\n", file);
			fputs("<gamma_logit_vintage_choice>", file);
		sprintf(data, "%f", FLAME_environment_variable_gamma_logit_vintage_choice);
		fputs(data, file);
		fputs("</gamma_logit_vintage_choice>\n", file);
			fputs("<delta_logit_vintage_choice>", file);
		sprintf(data, "%f", FLAME_environment_variable_delta_logit_vintage_choice);
		fputs(data, file);
		fputs("</delta_logit_vintage_choice>\n", file);
			fputs("<housing_alpha>", file);
		sprintf(data, "%f", FLAME_environment_variable_housing_alpha);
		fputs(data, file);
		fputs("</housing_alpha>\n", file);
			fputs("<housing_beta>", file);
		sprintf(data, "%f", FLAME_environment_variable_housing_beta);
		fputs(data, file);
		fputs("</housing_beta>\n", file);
			fputs("<housing_gamma>", file);
		sprintf(data, "%f", FLAME_environment_variable_housing_gamma);
		fputs(data, file);
		fputs("</housing_gamma>\n", file);
			fputs("<const_mortgage_initial_risk_of_default>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_mortgage_initial_risk_of_default);
		fputs(data, file);
		fputs("</const_mortgage_initial_risk_of_default>\n", file);
			fputs("<const_corporate_initial_risk_of_default>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_corporate_initial_risk_of_default);
		fputs(data, file);
		fputs("</const_corporate_initial_risk_of_default>\n", file);
			fputs("<max_duration_firm_loans_arrears>", file);
		sprintf(data, "%i", FLAME_environment_variable_max_duration_firm_loans_arrears);
		fputs(data, file);
		fputs("</max_duration_firm_loans_arrears>\n", file);
			fputs("<max_duration_firm_loans_npl>", file);
		sprintf(data, "%i", FLAME_environment_variable_max_duration_firm_loans_npl);
		fputs(data, file);
		fputs("</max_duration_firm_loans_npl>\n", file);
			fputs("<max_duration_mortgage_loans_arrears>", file);
		sprintf(data, "%i", FLAME_environment_variable_max_duration_mortgage_loans_arrears);
		fputs(data, file);
		fputs("</max_duration_mortgage_loans_arrears>\n", file);
			fputs("<max_duration_mortgage_loans_npl>", file);
		sprintf(data, "%i", FLAME_environment_variable_max_duration_mortgage_loans_npl);
		fputs(data, file);
		fputs("</max_duration_mortgage_loans_npl>\n", file);
			fputs("<max_dsti_for_repayment>", file);
		sprintf(data, "%f", FLAME_environment_variable_max_dsti_for_repayment);
		fputs(data, file);
		fputs("</max_dsti_for_repayment>\n", file);
			fputs("<max_id>", file);
		sprintf(data, "%i", FLAME_environment_variable_max_id);
		fputs(data, file);
		fputs("</max_id>\n", file);
			fputs("<number_of_banks_to_apply>", file);
		sprintf(data, "%i", FLAME_environment_variable_number_of_banks_to_apply);
		fputs(data, file);
		fputs("</number_of_banks_to_apply>\n", file);
			fputs("<const_number_of_banks>", file);
		sprintf(data, "%i", FLAME_environment_variable_const_number_of_banks);
		fputs(data, file);
		fputs("</const_number_of_banks>\n", file);
			fputs("<const_installment_periods>", file);
		sprintf(data, "%i", FLAME_environment_variable_const_installment_periods);
		fputs(data, file);
		fputs("</const_installment_periods>\n", file);
			fputs("<const_bank_dividend_rate>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_bank_dividend_rate);
		fputs(data, file);
		fputs("</const_bank_dividend_rate>\n", file);
			fputs("<bank_lambda>", file);
		sprintf(data, "%f", FLAME_environment_variable_bank_lambda);
		fputs(data, file);
		fputs("</bank_lambda>\n", file);
			fputs("<ecb_interest_rate>", file);
		sprintf(data, "%f", FLAME_environment_variable_ecb_interest_rate);
		fputs(data, file);
		fputs("</ecb_interest_rate>\n", file);
			fputs("<ecb_interest_rate_markdown>", file);
		sprintf(data, "%f", FLAME_environment_variable_ecb_interest_rate_markdown);
		fputs(data, file);
		fputs("</ecb_interest_rate_markdown>\n", file);
			fputs("<alfa>", file);
		sprintf(data, "%f", FLAME_environment_variable_alfa);
		fputs(data, file);
		fputs("</alfa>\n", file);
			fputs("<min_reserve_ratio>", file);
		sprintf(data, "%f", FLAME_environment_variable_min_reserve_ratio);
		fputs(data, file);
		fputs("</min_reserve_ratio>\n", file);
			fputs("<const_init_pd_corp>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_init_pd_corp);
		fputs(data, file);
		fputs("</const_init_pd_corp>\n", file);
			fputs("<const_init_lgd_corp>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_init_lgd_corp);
		fputs(data, file);
		fputs("</const_init_lgd_corp>\n", file);
			fputs("<const_init_pd_hh>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_init_pd_hh);
		fputs(data, file);
		fputs("</const_init_pd_hh>\n", file);
			fputs("<const_init_lgd_hh>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_init_lgd_hh);
		fputs(data, file);
		fputs("</const_init_lgd_hh>\n", file);
			fputs("<switch_bank_liquidity_full_rationing>", file);
		sprintf(data, "%i", FLAME_environment_variable_switch_bank_liquidity_full_rationing);
		fputs(data, file);
		fputs("</switch_bank_liquidity_full_rationing>\n", file);
			fputs("<switch_bank_capital_full_rationing>", file);
		sprintf(data, "%i", FLAME_environment_variable_switch_bank_capital_full_rationing);
		fputs(data, file);
		fputs("</switch_bank_capital_full_rationing>\n", file);
			fputs("<switch_non_risk_weighted_car>", file);
		sprintf(data, "%i", FLAME_environment_variable_switch_non_risk_weighted_car);
		fputs(data, file);
		fputs("</switch_non_risk_weighted_car>\n", file);
			fputs("<switch_ban_bank_dividends>", file);
		sprintf(data, "%i", FLAME_environment_variable_switch_ban_bank_dividends);
		fputs(data, file);
		fputs("</switch_ban_bank_dividends>\n", file);
			fputs("<switch_credit_rationing_unsound_firms>", file);
		sprintf(data, "%i", FLAME_environment_variable_switch_credit_rationing_unsound_firms);
		fputs(data, file);
		fputs("</switch_credit_rationing_unsound_firms>\n", file);
			fputs("<switch_credit_rationing_ponzi_firms>", file);
		sprintf(data, "%i", FLAME_environment_variable_switch_credit_rationing_ponzi_firms);
		fputs(data, file);
		fputs("</switch_credit_rationing_ponzi_firms>\n", file);
			fputs("<bank_data_quantile_upper_bound>", file);
		sprintf(data, "%f", FLAME_environment_variable_bank_data_quantile_upper_bound);
		fputs(data, file);
		fputs("</bank_data_quantile_upper_bound>\n", file);
			fputs("<bank_data_quantile_lower_bound>", file);
		sprintf(data, "%f", FLAME_environment_variable_bank_data_quantile_lower_bound);
		fputs(data, file);
		fputs("</bank_data_quantile_lower_bound>\n", file);
			fputs("<const_firm_leverage>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_firm_leverage);
		fputs(data, file);
		fputs("</const_firm_leverage>\n", file);
			fputs("<debt_rescaling_factor>", file);
		sprintf(data, "%f", FLAME_environment_variable_debt_rescaling_factor);
		fputs(data, file);
		fputs("</debt_rescaling_factor>\n", file);
			fputs("<target_leverage_ratio>", file);
		sprintf(data, "%f", FLAME_environment_variable_target_leverage_ratio);
		fputs(data, file);
		fputs("</target_leverage_ratio>\n", file);
			fputs("<target_liquidity_ratio>", file);
		sprintf(data, "%f", FLAME_environment_variable_target_liquidity_ratio);
		fputs(data, file);
		fputs("</target_liquidity_ratio>\n", file);
			fputs("<const_dividend_earnings_ratio>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_dividend_earnings_ratio);
		fputs(data, file);
		fputs("</const_dividend_earnings_ratio>\n", file);
			fputs("<switch_threshold_full_dividend_rule>", file);
		sprintf(data, "%i", FLAME_environment_variable_switch_threshold_full_dividend_rule);
		fputs(data, file);
		fputs("</switch_threshold_full_dividend_rule>\n", file);
			fputs("<const_threshold_full_dividend_rule>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_threshold_full_dividend_rule);
		fputs(data, file);
		fputs("</const_threshold_full_dividend_rule>\n", file);
			fputs("<switch_firm_illiquidity_debt_rescaling_rule>", file);
		sprintf(data, "%i", FLAME_environment_variable_switch_firm_illiquidity_debt_rescaling_rule);
		fputs(data, file);
		fputs("</switch_firm_illiquidity_debt_rescaling_rule>\n", file);
			fputs("<igfirm_dividend_payout_stretching_month>", file);
		sprintf(data, "%i", FLAME_environment_variable_igfirm_dividend_payout_stretching_month);
		fputs(data, file);
		fputs("</igfirm_dividend_payout_stretching_month>\n", file);
			fputs("<index_price_adj>", file);
		sprintf(data, "%f", FLAME_environment_variable_index_price_adj);
		fputs(data, file);
		fputs("</index_price_adj>\n", file);
			fputs("<index_price_adj_max>", file);
		sprintf(data, "%f", FLAME_environment_variable_index_price_adj_max);
		fputs(data, file);
		fputs("</index_price_adj_max>\n", file);
			fputs("<index_price_adj_min>", file);
		sprintf(data, "%f", FLAME_environment_variable_index_price_adj_min);
		fputs(data, file);
		fputs("</index_price_adj_min>\n", file);
			fputs("<trading_activity>", file);
		sprintf(data, "%i", FLAME_environment_variable_trading_activity);
		fputs(data, file);
		fputs("</trading_activity>\n", file);
			fputs("<trading_random>", file);
		sprintf(data, "%i", FLAME_environment_variable_trading_random);
		fputs(data, file);
		fputs("</trading_random>\n", file);
			fputs("<igfirm_fin_man_debug>", file);
		sprintf(data, "%i", FLAME_environment_variable_igfirm_fin_man_debug);
		fputs(data, file);
		fputs("</igfirm_fin_man_debug>\n", file);
			fputs("<switch_igfirm_endogenous_innovation_probability>", file);
		sprintf(data, "%i", FLAME_environment_variable_switch_igfirm_endogenous_innovation_probability);
		fputs(data, file);
		fputs("</switch_igfirm_endogenous_innovation_probability>\n", file);
			fputs("<igfirm_exogenous_innovation_probability>", file);
		sprintf(data, "%f", FLAME_environment_variable_igfirm_exogenous_innovation_probability);
		fputs(data, file);
		fputs("</igfirm_exogenous_innovation_probability>\n", file);
			fputs("<power_of_end_probability_function>", file);
		sprintf(data, "%f", FLAME_environment_variable_power_of_end_probability_function);
		fputs(data, file);
		fputs("</power_of_end_probability_function>\n", file);
			fputs("<igfirm_producer_debug>", file);
		sprintf(data, "%i", FLAME_environment_variable_igfirm_producer_debug);
		fputs(data, file);
		fputs("</igfirm_producer_debug>\n", file);
			fputs("<igfirm_exogenous_productivity_progress>", file);
		sprintf(data, "%f", FLAME_environment_variable_igfirm_exogenous_productivity_progress);
		fputs(data, file);
		fputs("</igfirm_exogenous_productivity_progress>\n", file);
			fputs("<symmetric_shock>", file);
		sprintf(data, "%i", FLAME_environment_variable_symmetric_shock);
		fputs(data, file);
		fputs("</symmetric_shock>\n", file);
			fputs("<energy_shock_start>", file);
		sprintf(data, "%i", FLAME_environment_variable_energy_shock_start);
		fputs(data, file);
		fputs("</energy_shock_start>\n", file);
			fputs("<energy_shock_end>", file);
		sprintf(data, "%i", FLAME_environment_variable_energy_shock_end);
		fputs(data, file);
		fputs("</energy_shock_end>\n", file);
			fputs("<const_energy_shock_intensity>", file);
		sprintf(data, "%f", FLAME_environment_variable_const_energy_shock_intensity);
		fputs(data, file);
		fputs("</const_energy_shock_intensity>\n", file);
			fputs("<energy_shock_frequency>", file);
		sprintf(data, "%i", FLAME_environment_variable_energy_shock_frequency);
		fputs(data, file);
		fputs("</energy_shock_frequency>\n", file);
			fputs("<innovation_by_random>", file);
		sprintf(data, "%i", FLAME_environment_variable_innovation_by_random);
		fputs(data, file);
		fputs("</innovation_by_random>\n", file);
			fputs("<ig_good_limited_offer>", file);
		sprintf(data, "%i", FLAME_environment_variable_ig_good_limited_offer);
		fputs(data, file);
		fputs("</ig_good_limited_offer>\n", file);
			fputs("<max_offer_ig_good>", file);
		sprintf(data, "%i", FLAME_environment_variable_max_offer_ig_good);
		fputs(data, file);
		fputs("</max_offer_ig_good>\n", file);
			fputs("<initial_frontier_firm_transition_phase>", file);
		sprintf(data, "%f", FLAME_environment_variable_initial_frontier_firm_transition_phase);
		fputs(data, file);
		fputs("</initial_frontier_firm_transition_phase>\n", file);
			fputs("<initial_productivity_firm>", file);
		sprintf(data, "%f", FLAME_environment_variable_initial_productivity_firm);
		fputs(data, file);
		fputs("</initial_productivity_firm>\n", file);
			fputs("<initial_specific_skills>", file);
		sprintf(data, "%f", FLAME_environment_variable_initial_specific_skills);
		fputs(data, file);
		fputs("</initial_specific_skills>\n", file);
			fputs("<strenght_of_tech_progress>", file);
		sprintf(data, "%i", FLAME_environment_variable_strenght_of_tech_progress);
		fputs(data, file);
		fputs("</strenght_of_tech_progress>\n", file);
			fputs("<linear_combination_pricing_ig_good>", file);
		sprintf(data, "%f", FLAME_environment_variable_linear_combination_pricing_ig_good);
		fputs(data, file);
		fputs("</linear_combination_pricing_ig_good>\n", file);
			fputs("<initial_capital_price_wage_ratio>", file);
		sprintf(data, "%f", FLAME_environment_variable_initial_capital_price_wage_ratio);
		fputs(data, file);
		fputs("</initial_capital_price_wage_ratio>\n", file);
			fputs("<union_strength>", file);
		sprintf(data, "%f", FLAME_environment_variable_union_strength);
		fputs(data, file);
		fputs("</union_strength>\n", file);
			fputs("<wage_update>", file);
		sprintf(data, "%f", FLAME_environment_variable_wage_update);
		fputs(data, file);
		fputs("</wage_update>\n", file);
			fputs("<min_vacancy>", file);
		sprintf(data, "%i", FLAME_environment_variable_min_vacancy);
		fputs(data, file);
		fputs("</min_vacancy>\n", file);
			fputs("<wage_reservation_update>", file);
		sprintf(data, "%f", FLAME_environment_variable_wage_reservation_update);
		fputs(data, file);
		fputs("</wage_reservation_update>\n", file);
			fputs("<region_cost>", file);
		sprintf(data, "%f", FLAME_environment_variable_region_cost);
		fputs(data, file);
		fputs("</region_cost>\n", file);
			fputs("<delivery_prob_if_critical_stock_0>", file);
		sprintf(data, "%f", FLAME_environment_variable_delivery_prob_if_critical_stock_0);
		fputs(data, file);
		fputs("</delivery_prob_if_critical_stock_0>\n", file);
			fputs("<number_applications>", file);
		sprintf(data, "%i", FLAME_environment_variable_number_applications);
		fputs(data, file);
		fputs("</number_applications>\n", file);
			fputs("<applications_per_day>", file);
		sprintf(data, "%i", FLAME_environment_variable_applications_per_day);
		fputs(data, file);
		fputs("</applications_per_day>\n", file);
			fputs("<lower_bound_firing>", file);
		sprintf(data, "%i", FLAME_environment_variable_lower_bound_firing);
		fputs(data, file);
		fputs("</lower_bound_firing>\n", file);
			fputs("<upper_bound_firing>", file);
		sprintf(data, "%i", FLAME_environment_variable_upper_bound_firing);
		fputs(data, file);
		fputs("</upper_bound_firing>\n", file);
			fputs("<logit_parameter_specific_skills>", file);
		sprintf(data, "%f", FLAME_environment_variable_logit_parameter_specific_skills);
		fputs(data, file);
		fputs("</logit_parameter_specific_skills>\n", file);
			fputs("<logit_parameter_general_skills>", file);
		sprintf(data, "%f", FLAME_environment_variable_logit_parameter_general_skills);
		fputs(data, file);
		fputs("</logit_parameter_general_skills>\n", file);
			fputs("<skill_update_acc_to_formula>", file);
		sprintf(data, "%i", FLAME_environment_variable_skill_update_acc_to_formula);
		fputs(data, file);
		fputs("</skill_update_acc_to_formula>\n", file);
			fputs("<gov_policy_unemployment_benefit_pct>", file);
		sprintf(data, "%f", FLAME_environment_variable_gov_policy_unemployment_benefit_pct);
		fputs(data, file);
		fputs("</gov_policy_unemployment_benefit_pct>\n", file);
			fputs("<gov_policy_money_financing_fraction>", file);
		sprintf(data, "%f", FLAME_environment_variable_gov_policy_money_financing_fraction);
		fputs(data, file);
		fputs("</gov_policy_money_financing_fraction>\n", file);
			fputs("<gov_policy_gdp_fraction_consumption>", file);
		sprintf(data, "%f", FLAME_environment_variable_gov_policy_gdp_fraction_consumption);
		fputs(data, file);
		fputs("</gov_policy_gdp_fraction_consumption>\n", file);
			fputs("<gov_policy_gdp_fraction_investment>", file);
		sprintf(data, "%f", FLAME_environment_variable_gov_policy_gdp_fraction_investment);
		fputs(data, file);
		fputs("</gov_policy_gdp_fraction_investment>\n", file);
			fputs("<no_regions_per_gov>", file);
		sprintf(data, "%i", FLAME_environment_variable_no_regions_per_gov);
		fputs(data, file);
		fputs("</no_regions_per_gov>\n", file);
			fputs("<subsidy_trigger_on>", file);
		sprintf(data, "%f", FLAME_environment_variable_subsidy_trigger_on);
		fputs(data, file);
		fputs("</subsidy_trigger_on>\n", file);
			fputs("<subsidy_trigger_off>", file);
		sprintf(data, "%f", FLAME_environment_variable_subsidy_trigger_off);
		fputs(data, file);
		fputs("</subsidy_trigger_off>\n", file);
			fputs("<gov_policy_swith_quantitative_easing>", file);
		sprintf(data, "%i", FLAME_environment_variable_gov_policy_swith_quantitative_easing);
		fputs(data, file);
		fputs("</gov_policy_swith_quantitative_easing>\n", file);
			fputs("<gov_policy_switch_human_capital_improvement>", file);
		sprintf(data, "%i", FLAME_environment_variable_gov_policy_switch_human_capital_improvement);
		fputs(data, file);
		fputs("</gov_policy_switch_human_capital_improvement>\n", file);
			fputs("<policy_exp_best_technology_subsidy>", file);
		sprintf(data, "%i", FLAME_environment_variable_policy_exp_best_technology_subsidy);
		fputs(data, file);
		fputs("</policy_exp_best_technology_subsidy>\n", file);
			fputs("<regional_policy_technology_subsidy>", file);
		sprintf(data, "%i", FLAME_environment_variable_regional_policy_technology_subsidy);
		fputs(data, file);
		fputs("</regional_policy_technology_subsidy>\n", file);
			fputs("<best_technology_subsidy_pct>", file);
		sprintf(data, "%f", FLAME_environment_variable_best_technology_subsidy_pct);
		fputs(data, file);
		fputs("</best_technology_subsidy_pct>\n", file);
			fputs("<innovation_switched_on>", file);
		sprintf(data, "%i", FLAME_environment_variable_innovation_switched_on);
		fputs(data, file);
		fputs("</innovation_switched_on>\n", file);
			fputs("<mr_start_price>", file);
		sprintf(data, "%f", FLAME_environment_variable_mr_start_price);
		fputs(data, file);
		fputs("</mr_start_price>\n", file);
			fputs("<mr_end_price>", file);
		sprintf(data, "%f", FLAME_environment_variable_mr_end_price);
		fputs(data, file);
		fputs("</mr_end_price>\n", file);
			fputs("<mr_price_increment>", file);
		sprintf(data, "%f", FLAME_environment_variable_mr_price_increment);
		fputs(data, file);
		fputs("</mr_price_increment>\n", file);
			fputs("<max_no_employees_product_innovation>", file);
		sprintf(data, "%i", FLAME_environment_variable_max_no_employees_product_innovation);
		fputs(data, file);
		fputs("</max_no_employees_product_innovation>\n", file);
			fputs("</environment>\n" , file);
	}
	
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(1, output_types, output_type_size))
	{
		current_xmachine_Firm_holder = Firm_start_Firm_state->agents;
			while(current_xmachine_Firm_holder)
			{
				write_Firm_agent(file, current_xmachine_Firm_holder->agent);

				current_xmachine_Firm_holder = current_xmachine_Firm_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(2, output_types, output_type_size))
	{
		current_xmachine_Household_holder = Household_start_Household_state->agents;
			while(current_xmachine_Household_holder)
			{
				write_Household_agent(file, current_xmachine_Household_holder->agent);

				current_xmachine_Household_holder = current_xmachine_Household_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(3, output_types, output_type_size))
	{
		current_xmachine_Mall_holder = Mall_start_Mall_state->agents;
			while(current_xmachine_Mall_holder)
			{
				write_Mall_agent(file, current_xmachine_Mall_holder->agent);

				current_xmachine_Mall_holder = current_xmachine_Mall_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(4, output_types, output_type_size))
	{
		current_xmachine_IGFirm_holder = IGFirm_IGFirm_start_state->agents;
			while(current_xmachine_IGFirm_holder)
			{
				write_IGFirm_agent(file, current_xmachine_IGFirm_holder->agent);

				current_xmachine_IGFirm_holder = current_xmachine_IGFirm_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(5, output_types, output_type_size))
	{
		current_xmachine_Eurostat_holder = Eurostat_start_Eurostat_state->agents;
			while(current_xmachine_Eurostat_holder)
			{
				write_Eurostat_agent(file, current_xmachine_Eurostat_holder->agent);

				current_xmachine_Eurostat_holder = current_xmachine_Eurostat_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(6, output_types, output_type_size))
	{
		current_xmachine_Bank_holder = Bank_start_Bank_state->agents;
			while(current_xmachine_Bank_holder)
			{
				write_Bank_agent(file, current_xmachine_Bank_holder->agent);

				current_xmachine_Bank_holder = current_xmachine_Bank_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(7, output_types, output_type_size))
	{
		current_xmachine_Government_holder = Government_start_Government_state->agents;
			while(current_xmachine_Government_holder)
			{
				write_Government_agent(file, current_xmachine_Government_holder->agent);

				current_xmachine_Government_holder = current_xmachine_Government_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(8, output_types, output_type_size))
	{
		current_xmachine_CentralBank_holder = CentralBank_start_Central_Bank_state->agents;
			while(current_xmachine_CentralBank_holder)
			{
				write_CentralBank_agent(file, current_xmachine_CentralBank_holder->agent);

				current_xmachine_CentralBank_holder = current_xmachine_CentralBank_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(9, output_types, output_type_size))
	{
		current_xmachine_ClearingHouse_holder = ClearingHouse_start_ClearingHouse_state->agents;
			while(current_xmachine_ClearingHouse_holder)
			{
				write_ClearingHouse_agent(file, current_xmachine_ClearingHouse_holder->agent);

				current_xmachine_ClearingHouse_holder = current_xmachine_ClearingHouse_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(10, output_types, output_type_size))
	{
		current_xmachine_NSA_holder = NSA_start_NSA_state->agents;
			while(current_xmachine_NSA_holder)
			{
				write_NSA_agent(file, current_xmachine_NSA_holder->agent);

				current_xmachine_NSA_holder = current_xmachine_NSA_holder->next;
			}
	}
	
	fputs("</states>\n" , file);

	/* Close the file */
	(void)fclose(file);
}

/** \fn void saveiterationdata(int iteration_number)
 * \brief Save X-machine memory to a file.
 * \param iteration_number The current iteration number.
 */
void saveiterationdata(int iteration_number)
{
	FLAME_output * current_FLAME_output;
	FLAME_output * current_FLAME_output2;
	int output_types[1000];
	int output_type_size = 0;

	/* For each output */
	for(current_FLAME_output = FLAME_outputs; current_FLAME_output != NULL; current_FLAME_output = current_FLAME_output->next)
	{
		/* If period/phase equates to current iteration */
		if(iteration_number%current_FLAME_output->period == current_FLAME_output->phase)
		{
			/* If output has already been handled */
			if(current_FLAME_output->flag == 0)
			{
				/* Check snapshot */
				if(current_FLAME_output->type == 0)
				{
					//snapshot_location = current_FLAME_output->location;
					output_types[0] = 0;
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, 1);
					/* Set flag to 1 and every output to same location */
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							current_FLAME_output2->flag = 1;
						}
					}
				}
				if(current_FLAME_output->type == 1)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 1;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 2)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 2;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 3)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 3;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 4)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 4;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 5)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 5;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 6)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 6;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 7)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 7;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 8)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 8;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 9)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 9;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 10)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 10;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}
			}
		}
	}
	/* Set flags back to 0 */
	for(current_FLAME_output = FLAME_outputs; current_FLAME_output != NULL; current_FLAME_output = current_FLAME_output->next)
	{
		current_FLAME_output->flag = 0;
	}
}

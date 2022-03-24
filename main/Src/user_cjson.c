#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"
#include "user_cjson.h"


int user_parse_seniverse_json(char *json_data)
{
    uint8_t i,j;
	uint8_t result_array_size = 0;
	uint8_t daily_array_size = 0;

	cJSON *item = NULL;
	cJSON *root = NULL;
	cJSON *results_root = NULL;
	cJSON *daily_root = NULL;
	user_seniverse_config_t user_sen_config;
    /* print the version */
    printf("Version: %s\n", cJSON_Version());
	root = cJSON_Parse(json_data);   /*json_data 为心知天气的原始数据*/ 
    if (!root) 
    {
      printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	  return  -1;
	}
       
    printf("%s\n\n", cJSON_Print(root));   /*将完整的数据以JSON格式打印出来*/


	cJSON *Presult = cJSON_GetObjectItem(root, "results");  /*results 的键值对为数组，*/ 
	        printf("%s\n", cJSON_Print(Presult));


	result_array_size = cJSON_GetArraySize(Presult);  /*求results键值对数组中有多少个元素*/
	printf("Presult array size is %d\n",result_array_size);

    for(i = 0;i < result_array_size;i++)
    {
		cJSON *item_results = cJSON_GetArrayItem(Presult, i);

        char *sresults = cJSON_PrintUnformatted(item_results);
		results_root = cJSON_Parse(sresults);
		if (!results_root) 
	    {
	      printf("Error before: [%s]\n",cJSON_GetErrorPtr());
		  return  -1;
		}
/*-------------------------------------------------------------------*/

		cJSON *Plocation = cJSON_GetObjectItem(results_root, "location");

	    item = cJSON_GetObjectItem(Plocation, "id");
		user_sen_config.id = cJSON_Print(item);
	        printf("id:%s\n", cJSON_Print(item));	/*逐个打印*/


	    item = cJSON_GetObjectItem(Plocation, "name");
		user_sen_config.name = cJSON_Print(item);
	        printf("name:%s\n", cJSON_Print(item));	

	    item = cJSON_GetObjectItem(Plocation, "country");
        user_sen_config.country = cJSON_Print(item);
	        printf("country:%s\n", cJSON_Print(item));	

	    item = cJSON_GetObjectItem(Plocation, "path");
        user_sen_config.path = cJSON_Print(item);
	        printf("path:%s\n", cJSON_Print(item));	

	    item = cJSON_GetObjectItem(Plocation, "timezone");
		user_sen_config.timezone = cJSON_Print(item);
	        printf("timezone:%s\n", cJSON_Print(item));	

		item = cJSON_GetObjectItem(Plocation, "timezone_offset");
		user_sen_config.timezone_offset = cJSON_Print(item);
	        printf("timezone_offset:%s\n", cJSON_Print(item));	
/*-------------------------------------------------------------------*/
		cJSON *Pdaily = cJSON_GetObjectItem(results_root, "daily");


		daily_array_size = cJSON_GetArraySize(Pdaily);
			printf("Pdaily array size is %d\n",daily_array_size);

        for(j = 0;j < daily_array_size;j++)
        {
			cJSON *item_daily = cJSON_GetArrayItem(Pdaily, j);
			
			char *sdaily = cJSON_PrintUnformatted(item_daily);

			daily_root = cJSON_Parse(sdaily);

			if (!daily_root) 
		    {
		      printf("Error before: [%s]\n",cJSON_GetErrorPtr());
			  return  -1;
			}


		    item = cJSON_GetObjectItem(daily_root, "date");
			user_sen_config.day_config[j].date = cJSON_Print(item);
		        printf("date:%s\n", cJSON_Print(item));		
			
		    item = cJSON_GetObjectItem(daily_root, "text_day");
			user_sen_config.day_config[j].text_day = cJSON_Print(item);
		        printf("text_day:%s\n", cJSON_Print(item));	

		    item = cJSON_GetObjectItem(daily_root, "code_day");
		    user_sen_config.day_config[j].code_day = cJSON_Print(item);
					        printf("code_day:%s\n", cJSON_Print(item));		

			item = cJSON_GetObjectItem(daily_root, "text_night");
			user_sen_config.day_config[j].text_night = cJSON_Print(item);
		        printf("text_night:%s\n", cJSON_Print(item));		

			item = cJSON_GetObjectItem(daily_root, "code_night");
			user_sen_config.day_config[j].code_night = cJSON_Print(item);
		        printf("code_night:%s\n", cJSON_Print(item));		

			item = cJSON_GetObjectItem(daily_root, "high");
			user_sen_config.day_config[j].high = cJSON_Print(item);
		        printf("high:%s\n", cJSON_Print(item));		

			item = cJSON_GetObjectItem(daily_root, "low");
			user_sen_config.day_config[j].low = cJSON_Print(item);
		        printf("low:%s\n", cJSON_Print(item));		

			item = cJSON_GetObjectItem(daily_root, "rainfall");
			user_sen_config.day_config[j].rainfall = cJSON_Print(item);
		        printf("rainfall:%s\n", cJSON_Print(item));		

			item = cJSON_GetObjectItem(daily_root, "precip");
			user_sen_config.day_config[j].precip = cJSON_Print(item);
		        printf("precip:%s\n", cJSON_Print(item));		

			item = cJSON_GetObjectItem(daily_root, "wind_direction");
			user_sen_config.day_config[j].wind_direction = cJSON_Print(item);
		        printf("wind_direction:%s\n", cJSON_Print(item));		

			item = cJSON_GetObjectItem(daily_root, "wind_direction_degree");
			user_sen_config.day_config[j].wind_direction_degree = cJSON_Print(item);
		        printf("wind_direction_degree:%s\n", cJSON_Print(item));		

			item = cJSON_GetObjectItem(daily_root, "wind_speed");
			user_sen_config.day_config[j].wind_speed = cJSON_Print(item);
		        printf("wind_speed:%s\n", cJSON_Print(item));		

			item = cJSON_GetObjectItem(daily_root, "wind_scale");
			user_sen_config.day_config[j].wind_scale = cJSON_Print(item);
		        printf("wind_scale:%s\n", cJSON_Print(item));		

			item = cJSON_GetObjectItem(daily_root, "humidity");
			user_sen_config.day_config[j].humidity = cJSON_Print(item);
		        printf("humidity:%s\n", cJSON_Print(item));		
			cJSON_Delete(daily_root);/*每次调用cJSON_Parse函数后，都要释放内存*/

        }
	/*-------------------------------------------------------------------*/
		item = cJSON_GetObjectItem(results_root, "last_update");
		user_sen_config.last_update = cJSON_Print(item);
		    printf("last_update:%s\n", cJSON_Print(item));	
		cJSON_Delete(results_root);  /*每次调用cJSON_Parse函数后，都要释放内存*/

    }

    printf("id:%s\n", user_sen_config.id);	
	printf("name:%s\n", user_sen_config.name);
	printf("country:%s\n", user_sen_config.country);
	printf("path:%s\n", user_sen_config.path);
	printf("timezone:%s\n", user_sen_config.timezone);
	printf("timezone_offset:%s\n", user_sen_config.timezone_offset);
	for(i = 0;i < daily_array_size;i++)
	{
    	printf("date:%s\n", user_sen_config.day_config[i].date); 
		printf("text_day:%s\n", user_sen_config.day_config[i].text_day); 
		printf("code_day:%s\n", user_sen_config.day_config[i].code_day); 
		printf("text_night:%s\n", user_sen_config.day_config[i].text_night); 
		printf("code_night:%s\n", user_sen_config.day_config[i].code_night); 
		printf("high:%s\n", user_sen_config.day_config[i].high); 
		printf("low:%s\n", user_sen_config.day_config[i].low); 
		printf("precip:%s\n", user_sen_config.day_config[i].precip); 
		printf("wind_direction:%s\n", user_sen_config.day_config[i].wind_direction); 
		printf("wind_direction_degree:%s\n", user_sen_config.day_config[i].wind_direction_degree); 
		printf("wind_speed:%s\n", user_sen_config.day_config[i].wind_speed); 
		printf("wind_scale:%s\n", user_sen_config.day_config[i].wind_scale); 
		printf("humidity:%s\n", user_sen_config.day_config[i].humidity); 
	}
	printf("last_update:%s\n", user_sen_config.last_update);
			
	cJSON_Delete(root);/*每次调用cJSON_Parse函数后，都要释放内存*/

	return  0;

}


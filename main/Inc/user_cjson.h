/**
 * @brief 心知天气（seniverse） 天气各项数据结构体
 */
typedef struct{
	char *date;
	char *text_day;
	char *code_day;
	char *text_night;
	char *code_night;
	char *high;
	char *low;
	char *rainfall;
	char *precip;
	char *wind_direction;
	char *wind_direction_degree;
	char *wind_speed;
	char *wind_scale;
	char *humidity;

} user_seniverse_day_config_t;


/**
 * @brief 心知天气（seniverse） 数据结构体
 */
typedef struct {
	char *id;
	char *name;
	char *country;
	char *path;
	char *timezone;
	char *timezone_offset;
    user_seniverse_day_config_t day_config[3];/*这里的3是指心知天气URL中的 days=3*/
	char *last_update;

} user_seniverse_config_t;

int user_parse_seniverse_json(char *json_data);
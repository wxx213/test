#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

char server[] = "localhost";
char user[] = "root";
char password[] = "wxx213";
char database[] = "db_students";

int main()
{
	MYSQL *sql,*retsql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int retval;
	int r,t;

	sql = mysql_init(NULL);
	if(sql == NULL){
		printf("mysql_init error\n");
		return 0;
	}
	retsql = mysql_real_connect(sql,server,user,password,database,0,NULL,0);
	if(retsql == NULL){
		printf("mysql_real_connect error\n");
		return 0;
	}
	retval = mysql_query(sql,"SELECT * FROM Student");
	if(retval != 0){
		printf("mysql_query error\n");
		return 0;
	}
	res = mysql_use_result(sql);
	if(res == NULL){
		printf("mysql_use_result error\n");
		return 0;
	}
	while((row = mysql_fetch_row(res)) != NULL){
		for(t=0;t<mysql_field_count(sql);t++){
			printf("%s  ",row[t]);
		}
		printf("\n");
	}
	mysql_free_result(res);
	mysql_close(sql);
	return 0;
}


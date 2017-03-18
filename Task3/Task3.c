#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
static int make(sqlite3 *db, char *zErrMsg, int rc, char *sql, const char* data){
 
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
    return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   sqlite3_stmt *res;
   char sql[512];
   const char* data = "Callback function called";
    
    char value[256];
	char answer;
    char answer_in_SELECT;
    int val=0;
    
    rc = sqlite3_open("Employees.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }


    while (answer != 'f'){
        
        printf("a) SELECT\nb) INSERT\nc) DELETE\nd) Parameterized queries\n");
		scanf("%c", &answer);
		getchar();

		switch (answer)
		{
		case 'a':
            printf("a) ALL\nb) Id\nc) Last name\nd)birthplace\n");
			scanf("%c", &answer_in_SELECT);
			getchar();

			switch (answer_in_SELECT)
			{
			case 'a':
				sprintf(sql, "SELECT * FROM Empl");
				break;

			case 'b':
				printf("Input id value: ");
				scanf("%s", &value);
				getchar();
				sprintf(sql, "SELECT * FROM Empl WHERE id=%s", value);
				break;

			case 'c':
				printf("Input last name value: ");
				scanf("%s", &value);
				getchar();
				sprintf(sql, "SELECT * FROM Empl WHERE lname='%s'", value);
				break;

			case 'd':
				printf("Input birthplace value: ");
				scanf("%s", &value);
				getchar();
				sprintf(sql, "SELECT * FROM Empl WHERE birthplace='%s'", value);
				break;

			default:
                sprintf(sql, "SELECT * FROM Empl");
				break;
			}
			make(db, zErrMsg, rc, sql, data);
                
			break;

		case 'b':
                
            printf("Input id: ");
			scanf("%s", &value);
			getchar();
            sprintf(sql, "INSERT INTO Empl VALUES(%s,", value);
                
			printf("Input fname: ");
			scanf("%s", &value);
			getchar();
            sprintf(sql, "%s '%s',", sql, value);
          
            printf("Input lname: ");
			scanf("%s", &value);
			getchar();
            sprintf(sql, "%s '%s',", sql, value);
    
            printf("Input sname: ");
			scanf("%s", &value);
			getchar();
            sprintf(sql, "%s '%s',", sql, value);

            printf("Input photo: ");
			scanf("%s", &value);
			getchar();
            sprintf(sql, "%s '%s',", sql, value);
    
            printf("Input birthday: ");
			scanf("%s", &value);
			getchar();
            sprintf(sql, "%s '%s',", sql, value);
                
            printf("Input birtplace: ");
			scanf("%s", &value);
			getchar();
            sprintf(sql, "%s '%s',", sql, value);

            printf("Input residential address: ");
			scanf("%s", &value);
			getchar();
            sprintf(sql, "%s '%s',", sql, value);

            printf("Input department: ");
			scanf("%s", &value);
			getchar();
            sprintf(sql, "%s %s,", sql, value);
    
            printf("Input post: ");
			scanf("%s", &value);
			getchar();
            sprintf(sql, "%s '%s',", sql, value);
    
            printf("Input date_recruitment: ");
			scanf("%s", &value);
			getchar();
            sprintf(sql, "%s '%s')", sql, value);
 
            make(db, zErrMsg, rc, sql, data);
            break;

		case 'c':
			printf("Input field=value\n");
			scanf("%s", &value);
			getchar();

            sprintf(sql, "DELETE FROM Empl WHERE %s",value);
            make(db, zErrMsg, rc, sql, data);
            break;
                
        case 'd':
            sprintf(sql, "SELECT id, fname FROM Empl WHERE Id = @id");
        
            rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

            if (rc == SQLITE_OK) {

                int idx = sqlite3_bind_parameter_index(res, "@id");
                printf("Input value of id: ");
                scanf("%d", &val);
                getchar();
                sqlite3_bind_int(res, idx, val);

            } else {

                fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
            }

            int step = sqlite3_step(res);

            if (step == SQLITE_ROW) {

                printf("%s: ", sqlite3_column_text(res, 0));
                printf("%s\n", sqlite3_column_text(res, 1));

            } 

            sqlite3_finalize(res);
                
            break;
		default:
                printf("End");
			break;
		}

      }

   sqlite3_close(db);
   return 0;
}
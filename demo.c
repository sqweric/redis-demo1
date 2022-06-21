#include <stdio.h>
#include "hiredis.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main() {

    // 连接Redis服务
    redisContext *context = redisConnect("192.168.31.72", 6379);
    if (context == NULL || context->err) {
        if (context) {
            printf("%s\n", context->errstr);
        } else {
            printf("redisConnect error\n");
        }
        exit(EXIT_FAILURE);
    }

//密码
    redisReply* reply = (struct redisReply*)redisCommand(context,"Auth %s","123321");
    printf("auth ret is %s\n",reply->str);
    freeReplyObject(reply);







    //执行命令
    // Set Key Value
    char *key = "str";
    char *val = "Hello World";
    /*SET key value */
    reply = redisCommand(context, "SET %s %s", key, val);
    printf("type : %d\n", reply->type);
    if (reply->type == REDIS_REPLY_STATUS) {
        /*SET str Hello World*/
        printf("SET %s %s\n", key, val);
    }
    freeReplyObject(reply);

    // GET Key
    reply = redisCommand(context, "GET %s", key);
    if (reply->type == REDIS_REPLY_STRING) {
        /*GET str Hello World*/
        printf("GET str %s\n", reply->str);
        /*GET len 11*/
        printf("GET len %ld\n", reply->len);
    }
    freeReplyObject(reply);

//释放连接
    redisFree(context);
    return EXIT_SUCCESS;
}
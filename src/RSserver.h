#ifndef RS_SERVER_H__
#define RS_SERVER_H__

typedef struct args args_t;

typedef void (*work_fn_t)(void *par);
typedef void (*send_fn_t)(args_t *arg, int rsp, rlen_t len, void *buf);
typedef int  (*buf_fn_t) (args_t *arg, void *buf, rlen_t len);

/* definition of a server */
typedef struct server {
    int ss;               /* server socket */
    int unix_socket;      /* 0 = TCP/IP, 1 = unix socket */
    work_fn_t connected;  /* function called for each new connection */
    work_fn_t fin;        /* optional finalization function */
    send_fn_t send_resp;  /* send response */
    buf_fn_t  send;       /* direct send */
    buf_fn_t  recv;       /* direct receive */
} server_t;

server_t *create_server(int port, const char *localSocketName);
int add_server(server_t *srv);
int rm_server(server_t *srv);

/* some generic implementations */
void server_fin(void *x);
int server_recv(args_t *arg, void *buf, rlen_t len);
int server_send(args_t *arg, void *buf, rlen_t len);

void stop_server_loop();
void serverLoop();

#endif
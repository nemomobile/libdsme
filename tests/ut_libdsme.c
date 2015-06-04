/**
   @file ut_libdsme.c

   Unit tests for libdsme.
   <p>
   Copyright (C) 2013 Jolla Ltd.

   @author Martin Kampas <martin.kampas@tieto.com>

   This file is part of Dsme.

   Dsme is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 2.1 as published by the Free Software Foundation.

   Dsme is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with Dsme.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * some glibc versions seems to mistakenly define ucred behind __USE_GNU;
 * work around by #defining _GNU_SOURCE
 */
#ifndef __cplusplus
#define _GNU_SOURCE
#endif

#include <check.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "../include/dsme/messages.h"
#include "../include/dsme/protocol.h"
#include "../include/dsme/state.h"

static const char* const TMP_SOCKFILE = "/tmp/ut_libdsme.sock";

static int mock_ready_semid = 0;
static int mock_ready_semop(int op);

static int mock(void)
{
    int fd;
    int client_fd;
    struct sockaddr_un laddr;

    memset(&laddr, 0, sizeof(laddr));
    laddr.sun_family = AF_UNIX;
    strncpy(laddr.sun_path, TMP_SOCKFILE, sizeof(laddr.sun_path) - 1);
    laddr.sun_path[sizeof(laddr.sun_path) - 1] = 0;

    fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("MOCK: socket() failed");
        return EXIT_FAILURE;
    }

    unlink(TMP_SOCKFILE);
    if (bind(fd, (struct sockaddr*)&laddr, sizeof(laddr)) == -1) {
        perror("MOCK: bind() failed");
        return EXIT_FAILURE;
    }
    chmod(TMP_SOCKFILE, 0666);

    if (listen(fd, 1) == -1) {
        perror("MOCK: listen() failed");
        return EXIT_FAILURE;
    }

    if (mock_ready_semop(1) == -1) {
        perror("MOCK: semop() failed");
        return EXIT_FAILURE;
    }

    if ((client_fd = accept(fd, NULL, 0)) == -1) {
        perror("MOCK: accept() failed");
        return EXIT_FAILURE;
    }

    dsmesock_connection_t* connection = dsmesock_init(client_fd);
    if (connection == NULL) {
        puts("MOCK: dsmesock_init() failed");
        return EXIT_FAILURE;
    }

    // Flags set (exactly) to O_NONBLOCK by dsmesock_init() - we do not want this during testing
    if (fcntl(connection->fd, F_SETFL, 0) == -1) {
        perror("fcntl failed");
    }

    // Allow to exit immediately
    struct linger linger;
    linger.l_onoff  = 1;
    linger.l_linger = 2;
    setsockopt(client_fd, SOL_SOCKET, SO_LINGER, &linger, sizeof(linger));

    dsmemsg_generic_t* msg = (dsmemsg_generic_t*)dsmesock_receive(connection);
    if (msg == NULL) {
        puts("MOCK: dsmesock_receive() failed");
        return EXIT_FAILURE;
    }

    DSM_MSGTYPE_STATE_QUERY* state_query_msg = DSMEMSG_CAST(DSM_MSGTYPE_STATE_QUERY, msg);
    if (state_query_msg == NULL) {
        puts("MOCK: DSMEMSG_CAST() failed");
        return EXIT_FAILURE;
    }

    DSM_MSGTYPE_STATE_REQ_DENIED_IND reply =
        DSME_MSG_INIT(DSM_MSGTYPE_STATE_REQ_DENIED_IND);
    reply.state = DSME_STATE_TEST;

    dsmesock_send_with_extra(connection, &reply, strlen("a-reason"), "a-reason");

    return EXIT_SUCCESS;
}

START_TEST(test_message)
{
    const u_int32_t id = 42;

    dsmemsg_generic_t* msg = dsmemsg_new(id, sizeof(dsmemsg_generic_t), sizeof(int));

    ck_assert(msg != NULL);
    ck_assert_int_eq(id, dsmemsg_id(msg));

    free(msg);
}
END_TEST

START_TEST(test_send_receive)
{
    dsmesock_connection_t* connection = dsmesock_connect();
    ck_assert(connection != NULL);

    // Flags set (exactly) to O_NONBLOCK by dsmesock_init() - we do not want this during testing
    if (fcntl(connection->fd, F_SETFL, 0) == -1) {
        ck_abort_msg("fcntl failed");
    }

    DSM_MSGTYPE_STATE_QUERY msg = DSME_MSG_INIT(DSM_MSGTYPE_STATE_QUERY);

    dsmesock_broadcast(&msg);

    dsmemsg_generic_t* reply = (dsmemsg_generic_t*)dsmesock_receive(connection);
    ck_assert(reply != NULL);

    DSM_MSGTYPE_STATE_REQ_DENIED_IND* state_reply =
        DSMEMSG_CAST(DSM_MSGTYPE_STATE_REQ_DENIED_IND, reply);
    ck_assert(state_reply != NULL);

    ck_assert(state_reply->state == DSME_STATE_TEST);

    const char* reason = DSMEMSG_EXTRA(state_reply);
    ck_assert(reason != NULL);
    ck_assert(strcmp(reason, "a-reason") == 0);

    free(reply);

    dsmesock_close(connection);
}
END_TEST

static Suite* libdsme_suite(void)
{
    Suite* s = suite_create ("libdsme");

    TCase* tc = tcase_create("libdsme");

    tcase_add_test (tc, test_message);
    tcase_add_test (tc, test_send_receive);

    suite_add_tcase (s, tc);

    return s;
}

int main(void)
{
    setenv("DSME_SOCKFILE", TMP_SOCKFILE, 1);

    if ((mock_ready_semid = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT)) == -1) {
        perror("semget() failed");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == 0) {
        _exit(mock());
    } else if (pid < 0) {
        return EXIT_FAILURE;
    }

    if (mock_ready_semop(-1) == -1) {
        perror("semop() failed");
        return EXIT_FAILURE;
    }

    int number_failed;
    Suite* s = libdsme_suite();
    SRunner* sr = srunner_create(s);

    srunner_set_xml(sr, "/tmp/result.xml");
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free (sr);

    waitpid(pid, NULL, 0);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

static int mock_ready_semop(int op)
{
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = op;
    sops.sem_flg = 0;

    struct timespec timeout;
    timeout.tv_sec = 10;
    timeout.tv_nsec = 0;

    return semtimedop(mock_ready_semid, &sops, 1, &timeout);
}

/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2023 Meta Platforms, Inc. and affiliates.
 */

#include "shared/response.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shared/mem.h"

int bf_response_new_success(struct bf_response **response, size_t data_len,
                            const char *data)
{
    __cleanup_bf_response__ struct bf_response *_response = NULL;

    assert(response);
    assert(data);

    _response = calloc(1, sizeof(*_response) + data_len);
    if (!_response)
        return -ENOMEM;

    _response->type = BF_RES_SUCCESS;
    memcpy(_response->data, data, data_len);
    _response->data_len = data_len;

    *response = TAKE_PTR(_response);

    return 0;
}

int bf_response_new_failure(struct bf_response **response, int error)
{
    __cleanup_bf_response__ struct bf_response *_response = NULL;

    assert(response);

    printf("Allocating %zu bytes for response\n", sizeof(*_response));
    _response = calloc(1, sizeof(*_response));
    if (!_response)
        return -ENOMEM;

    _response->type = BF_RES_FAILURE;
    _response->error = error;

    *response = TAKE_PTR(_response);

    return 0;
}

void bf_response_free(struct bf_response **response)
{
    free(*response);
    *response = NULL;
}

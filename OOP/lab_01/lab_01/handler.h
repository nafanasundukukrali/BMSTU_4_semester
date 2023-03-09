#ifndef HANDLER_H
#define HANDLER_H

#include "error.h"
#include "request.h"

err_t handler_action(request_type_t request, action_params_t *params);

#endif // HANDLER_H

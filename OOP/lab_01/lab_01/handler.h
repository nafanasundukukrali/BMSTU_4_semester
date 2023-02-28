#ifndef HANDLER_H
#define HANDLER_H

#include "error.h"
#include "request.h"

err_t handler_action(request_t request, void *params);


#endif // HANDLER_H

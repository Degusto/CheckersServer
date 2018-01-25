//  Copyright (C) 2013-2014 Michal Kalewski  <mkalewski at cs.put.poznan.pl>
//
//  This program comes with ABSOLUTELY NO WARRANTY.
//  THIS IS FREE SOFTWARE, AND YOU ARE WELCOME TO REDISTRIBUTE IT UNDER THE
//  TERMS AND CONDITIONS OF THE MIT LICENSE.  YOU SHOULD HAVE RECEIVED A COPY
//  OF THE LICENSE ALONG WITH THIS SOFTWARE; IF NOT, YOU CAN DOWNLOAD A COPY
//  FROM HTTP://WWW.OPENSOURCE.ORG.

#include "Models/Server.h"

int main() {
    Server server = Server();

    server.start();

    return EXIT_SUCCESS;
}
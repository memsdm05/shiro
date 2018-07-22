#include "../config/bancho_file.hh"
#include "../logger/route_logger.hh"
#include "../thirdparty/loguru.hh"
#include "impl/root_route.hh"
#include "routes.hh"

void shiro::routes::init() {
    server.loglevel(crow::LogLevel::Info);
    crow::logger::setHandler(std::make_shared<logging::route_logger>().get());

    init_routes();

    try {
        server.concurrency(config::bancho::concurrency);
        server.bindaddr(config::bancho::host).port((uint16_t) config::bancho::port).multithreaded().run();
    } catch (const boost::system::system_error &ex) {
        LOG_S(FATAL) << "Unable to start server: " << ex.what() << ".";
    }
}

void shiro::routes::init_routes() {
    CROW_ROUTE(server, "/").methods("GET"_method, "POST"_method)(root::handle);
}

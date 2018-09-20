#include "../thirdparty/cpptoml.hh"
#include "../thirdparty/loguru.hh"
#include "bancho_file.hh"
#include "cli_args.hh"

static std::shared_ptr<cpptoml::table> config_file = nullptr;

std::string shiro::config::bancho::host = "127.0.0.1";
uint16_t shiro::config::bancho::port = 8080;
uint16_t shiro::config::bancho::concurrency = 64;

std::string shiro::config::bancho::api_key = "osu! API key";

void shiro::config::bancho::parse() {
    if (config_file != nullptr)
        LOG_S(INFO) << "Re-parsing bancho.toml file...";

    try {
        config_file = cpptoml::parse_file("bancho.toml");
    } catch (const cpptoml::parse_exception &ex) {
        LOG_S(FATAL) << "Failed to parse bancho.toml file: " << ex.what() << ".";
    }

    host = config_file->get_qualified_as<std::string>("server.host").value_or("127.0.0.1");
    port = config_file->get_qualified_as<uint16_t>("server.port").value_or(8080);
    concurrency = config_file->get_qualified_as<uint16_t>("server.concurrency").value_or(64);

    api_key = config_file->get_qualified_as<std::string>("api.key").value_or("osu! API key");

    LOG_S(INFO) << "Successfully parsed bancho.toml.";

    cli::cli_app.add_option("--bancho-host", host, "Host that Bancho should bind to");
    cli::cli_app.add_option("--bancho-port", port, "Port that Bancho should bind to");
    cli::cli_app.add_option("--bancho-concurrency", concurrency, "Amount of concurrent connections that should be handled");

    cli::cli_app.add_option("--bancho-api-key", api_key, "API key for accessing official osu!Bancho API");
}

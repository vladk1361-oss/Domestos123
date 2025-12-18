#include "crow_all.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/check").methods("POST"_method)
    ([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("number")) {
            return crow::response(400, "{\"error\":\"Number not provided\"}");
        }

        int number = body["number"].i();

        crow::json::wvalue result;
        result["positive"] = number > 0;
        result["even"] = number % 2 == 0;

        return crow::response(result);
    });

    app.port(18080).run();
}
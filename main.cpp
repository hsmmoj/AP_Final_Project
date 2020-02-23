#include "App.hpp"
#include "handlers.hpp"
#include "my_server.hpp"
using namespace std;

main(int argc, char **argv) {
    App* app =  new App();
    srand(time(NULL)); // for rand
    try {
        MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
            server.setNotFoundErrPage("static/404.html");
            server.get("/signup", new ShowPage("static/signup.html"));
            server.post("/signup", new SignupHandler(app));

            server.get("/login", new ShowPage("static/logincss.html"));
            server.post("/login", new LoginHandler(app));

            server.get("/logout", new LogoutHandler(app));

            server.get("/home", new HomePageHandler(app));
            server.get("/upload", new ShowPage("static/upload.html"));
            server.post("/upload", new UploadHandler(app));

            server.get("/addOffer", new ShowAddOfferPage(app));
            server.post("/addOffer", new AddOfferHandler(app));

            server.post("/wallet", new WalletHandler(app));
            server.get("/wallet", new WalletHandler(app));

            server.post("/charge", new ChargeHandler(app));

            server.get("/product", new ProductDetailHandler(app));
            server.post("/comment", new CommentHandler(app));
            server.post("/addToCart", new AddToCartHandler(app));
            server.get("/cart", new CartHandler(app));
            server.get("/buy", new BuyHandler(app));
            server.run();
    } catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }
    return 0;
}
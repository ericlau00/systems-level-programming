struct wallet {
    char* first_name;
    char* last_name;
    int money; 
};

struct wallet createWallet();

int printWallet(struct wallet* wallet);

int spendMoney(struct wallet* wallet, int amount);

int gainMoney(struct wallet* wallet, int amount);

int changeOwner(struct wallet* wallet, char* first_name, char* last_name);
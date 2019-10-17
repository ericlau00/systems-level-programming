struct wallet {
    char* first_name;
    char* last_name;
    double money; 
};

struct wallet * createWallet();

int printWallet(struct wallet wallet);

int spendMoney(double amount);
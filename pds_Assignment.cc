#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdexcept>

class KeyValueDatabase{
public:
    void begin_transaction() {
        if (transaction_in_progress) {
            throw std::runtime_error("Transaction already in progress( BEGIN..)");
        }
        transaction_in_progress = true;
        std::cout<<"Transaction started"<<std::endl;
    }

    void put(const std::string& key, int value) {
        if (!transaction_in_progress) {
            throw std::runtime_error("Transaction not in progress(IN PUT)");
        }
        transaction_log.emplace_back(key, data[key]);
        data[key] = value;
        std::cout<<key<<"--"<<value<<" has been added(but not committed)."<<std::endl;
    }

    int get(const std::string& key) {
        if (data.find(key) == data.end()) {
            std::cout<<"The entered key is not present in database.(IN GET)"<<std::endl;
        }

        return data[key];
    }

    void commit() {
        if (!transaction_in_progress) {
            throw std::runtime_error("Transaction not in progress(IN COMMIT)");
        }
        transaction_in_progress = false;
        transaction_log.clear();
    }

    void rollback() {
        if (!transaction_in_progress) {
            throw std::runtime_error("Transaction not in progress(IN ROLLBACK)");
        }
        for (auto& [key, value] : transaction_log) {
            data[key] = value;
        }
        transaction_in_progress = false;
        transaction_log.clear();
    }

private:
    std::unordered_map<std::string, int> data;
    bool transaction_in_progress = false;
    std::vector<std::pair<std::string, int>> transaction_log;
};

int main()
{
    KeyValueDatabase db;
    // should return null, because "A" doesn’t exist in the DB yet
    std::cout << db.get("A") << std::endl;

    // should throw an error because a transaction is not in progress
    try
    {
        // Attempt to call put function
        db.put("A", 5) ;
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // starts a new transaction
    try
    {
        // Attempt to call put function
        db.begin_transaction();
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // set’s value of A to 5, but it's not committed yet
    try
    {
        // Attempt to call put function
        db.put("A", 5);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }


    // should return null, because updates to A are not committed yet
    try
    {
        // Attempt to call put function
        db.get("A");
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // update A’s value to 6 within the transaction
    try
    {
        // Attempt to call put function
        db.put("A", 6);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // commits the open transaction
    try
    {
        // Attempt to call put function
        db.commit();
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // should return 6, that was the last value of A to be committed
    try
    {
        // Attempt to call put function
        db.get("A");
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // throws an error, because there is no open transaction
    try
    {
        // Attempt to call put function
        db.commit();
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // throws an error because there is no ongoing transaction
    try
    {
        // Attempt to call put function
        db.rollback();
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // should return null because B does not exist in the database
    try
    {
        // Attempt to call put function
        db.get("B");
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // starts a new transaction
    try
    {
        // Attempt to call put function
        db.begin_transaction();
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Set key B’s value to 10 within the transaction
    try
    {
        // Attempt to call put function
        db.put("B", 10);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Rollback the transaction - revert any changes made to B
    try
    {
        // Attempt to call put function
        db.rollback();
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Should return null because changes to B were rolled back
    try
    {
        // Attempt to call put function
        db.get("B");
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;


}

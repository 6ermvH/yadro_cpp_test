#ifndef MANAGER_USER_HPP
#define MANAGER_USER_HPP

class ManagerUser {
public:
    ManagerUser() = default;
    ~ManagerUser() = default;

    void add(const std::string& username, user_id_t user_id);
    void wait(const std::string& username);
    void unwait(const std::string& username);
    void remove(const std::string& username);
    bool has_user(const std::string& username) const;

private:
    std::unordered_map<std::string, user_id_t> user_map_;
    std::list<user_id_t> waiting_group_; 
};

#endif // !MANAGER_USER_HPP

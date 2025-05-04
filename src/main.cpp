#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "club.hpp"
#include "event.hpp"

auto parse_file(std::ifstream& ifs) -> std::vector<std::string>;
auto bad_string(const std::vector<std::string>& lines) -> std::string;
auto parse_club(const std::vector<std::string>& lines) -> std::shared_ptr<Club>;

auto main(int argc, char* argv[]) -> int {
  if (argc < 2) {
    std::cerr << "Bad arguments";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Bad file";
    return 1;
  }
  auto lines = parse_file(file);
  std::string bad = bad_string(lines);
  if (!bad.empty()) {
    std::cerr << bad;
    return 1;
  }

  std::istringstream ss(lines[1]);
  std::string start_str;
  std::string end_str;
  ss >> start_str >> end_str;
  utils::Time start(start_str);
  utils::Time end(end_str);

  std::cout << start.to_string() << '\n';

  auto club = parse_club(lines);
  std::deque<std::unique_ptr<Event> > events;

  for (std::size_t i = 3; i < lines.size(); ++i) {
    std::istringstream ss(lines[i]);
    std::string time_str;
    int id;
    std::string name;
    ss >> time_str >> id >> name;
    utils::Time t(time_str);
    std::unique_ptr<Event> ev;
    switch (id) {
      case 1:
        events.push_back(std::make_unique<ClientComeIn>(club, t, id, name));
        break;
      case 2:
        std::size_t pc_id;
        ss >> pc_id;
        --pc_id;
        events.push_back(
            std::make_unique<ClientUsePC>(club, t, id, name, pc_id));
        break;
      case 3:
        events.push_back(std::make_unique<ClientWait>(club, t, id, name));
        break;
      case 4:
        events.push_back(std::make_unique<ClientLeave>(club, t, id, name));
        break;
    }
  }

  while (!events.empty()) {
    auto event = std::move(events.front());
    events.pop_front();
    auto result = event->handle();
    std::cout << *event << '\n';
    if (result) {
      events.push_front(std::move(result));
    }
  }

  auto users = club->get_users();
  std::ranges::sort(users);
  for (auto& username : users) {
    auto ev = std::make_unique<ClientLeave>(club, end, 11, username);
    ev->handle();
    std::cout << *ev << '\n';
  }

  std::cout << end.to_string() << '\n';

  auto revenue = club->get_revenue();
  for (std::size_t i = 0; i < revenue.size(); ++i) {
    std::cout << i + 1 << ' ' << revenue[i].first << ' '
              << revenue[i].second.to_string() << '\n';
  }
}

auto parse_file(std::ifstream& ifs) -> std::vector<std::string> {
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(ifs, line)) {
    if (!line.empty()) {
      lines.push_back(line);
    }
  }
  return lines;
}

auto bad_string(const std::vector<std::string>& lines) -> std::string {
  if (lines.size() < 3) {
    return lines.empty() ? "" : lines[0];
  }

  {
    std::istringstream ss(lines[0]);
    std::size_t pc_count;
    std::string extra;
    if (!(ss >> pc_count) || pc_count == 0 || (ss >> extra)) {
      return lines[0];
    }
  }

  {
    std::istringstream ss(lines[1]);
    std::string open_str;
    std::string close_str;
    std::string extra;
    ss >> open_str >> close_str;
    if (open_str.size() != 5 || close_str.size() != 5 || (ss >> extra)) {
      return lines[1];
    }
    try {
      utils::Time open(open_str);
      utils::Time close(close_str);
    } catch (...) {
      return lines[1];
    }
  }

  {
    std::istringstream ss(lines[2]);
    std::uint32_t price;
    std::string extra;
    if (!(ss >> price) || price == 0 || (ss >> extra)) {
      return lines[2];
    }
  }

  for (std::size_t i = 3; i < lines.size(); ++i) {
    std::istringstream ss(lines[i]);
    std::string time_str;
    int id;

    if (!(ss >> time_str >> id)) {
      return lines[i];
    }

    if (time_str.size() != 5) {
      return lines[i];
    }

    try {
      utils::Time t(time_str);
    } catch (...) {
      return lines[i];
    }

    std::string name;
    if (!(ss >> name)) {
      return lines[i];
    }

    if (id == 1 || id == 3 || id == 4) {
      std::string extra;
      if (ss >> extra) {
        return lines[i];
      }
    } else if (id == 2) {
      int pc_id;
      std::string extra;
      if (!(ss >> pc_id) || pc_id <= 0 || (ss >> extra)) {
        return lines[i];
      }
    } else {
      return lines[i];
    }
  }

  return "";
}
auto parse_club(const std::vector<std::string>& lines)
    -> std::shared_ptr<Club> {
  std::size_t pc_count = std::stoul(lines[0]);
  utils::Time open(lines[1].substr(0, 5));
  utils::Time close(lines[1].substr(6, 5));
  std::uint32_t price = std::stoul(lines[2]);

  return std::make_shared<Club>(pc_count, price, open, close);
}

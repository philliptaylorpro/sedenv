#include <iostream>
#include <strings.h>
#include <vector>

using namespace std;

#define env_var_list vector<string>

string read_input();
env_var_list get_substituion_list(string config);

// env_var_name variables shouldn't have __xx__ wrappers
string get_env_value(string env_var_name);
string replace_text(string text, string env_var_name, string replace);

int main(int argc, char *argv[]) {

  if (argc > 1) {
    if (string(argv[1]) == "--help" || string(argv[1]) == "-h") {
      cout << "https://github.com/philliptaylorpro/sedenv/blob/master/README.md" << endl;
      return 0;
    }
  }

  string config = read_input();

  const env_var_list env_var_names = get_substituion_list(config);
  for (env_var_list::const_iterator env_var_name = env_var_names.begin(); env_var_name != env_var_names.end(); ++env_var_name) {
    clog << "ENV VAR SUBSTITUTION: " << *env_var_name << endl;
    string env_var_value = get_env_value(*env_var_name);
    config = replace_text(config, *env_var_name, env_var_value);
  }

  cout << config;
  return 0;
}

string read_input() {
  string input;
  for (std::string line; std::getline(std::cin, line);) {
      input += line;
      input += '\n';
  }
  return input;
}

env_var_list get_substituion_list(string config) {
  env_var_list retval;

  char prev = '0';
  bool inStr = false;
  string collected;

  for (std::string::iterator it = config.begin(); it != config.end(); ++it) {
    if (*it == '_' && prev == '_') {
      if (inStr) {
        inStr = false;
        collected.pop_back(); // __ENV_VAR__ collects as ENV_VAR_  without this due to two character flag.
        retval.push_back(collected);
        collected = "";
      } else {
        inStr = true;
        collected = "";
      }
    } else {
      if (inStr)
        collected += *it;
    }

    prev = *it;
  }

  return retval;
}

string get_env_value(string env_var_name) {
  const char *raw_value = std::getenv(env_var_name.c_str());
  if (raw_value)
    return string(raw_value);
  else
    return string("");
}

string replace_text(string text, string find, string replace) {
  text.replace(text.find("__" + find + "__"), find.length() + 4, replace);
  return text;
}

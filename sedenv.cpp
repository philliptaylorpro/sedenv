#include <iostream>
#include <strings.h>
#include <vector>

using namespace std;

struct Substitution {
  string text_in_config;
  string env_var;
};

struct SubstitutionList {
  bool success;
  string error;
  vector<Substitution> env_vars;
};

SubstitutionList get_substituion_list(string config);
string get_env_value(string env_var_name);
string replace_text(string text, string find, string replace);

int main(int argc, char *argv[]) {
  string config;

  if (argc > 1) {
    if (string(argv[1]) == "--help" || string(argv[1]) == "-h") {
      cout << "https://github.com/philliptaylorpro/sedenv/blob/master/README.md" << endl;
      return 0;
    }
  }

  for (std::string line; std::getline(std::cin, line);) {
      config += line;
      config += '\n';
  }

  const SubstitutionList sl = get_substituion_list(config);
  for (vector<Substitution>::const_iterator iter = sl.env_vars.begin(); iter != sl.env_vars.end(); ++iter) {
    clog << "ENV VAR SUBSTITUTION: " << iter->env_var << endl;
    string env_var_value = get_env_value(iter->env_var);
    config = replace_text(config, iter->text_in_config, env_var_value);
  }

  cout << config;
  return 0;
}

SubstitutionList get_substituion_list(string config) {
  SubstitutionList retval;
  retval.success = true;

  char prev = '0';
  bool inStr = false;
  string collected;

  for (std::string::iterator it = config.begin(); it != config.end(); ++it) {
    if (*it == '_' && prev == '_') {
      if (inStr) {
        inStr = false;
        collected.pop_back(); // __ENV_VAR__ collects as ENV_VAR_  without this due to two character flag.
        Substitution newSub;
        newSub.env_var = collected;
        newSub.text_in_config = "__" + collected + "__";
        retval.env_vars.push_back(newSub);
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
  text.replace(text.find(find), find.length(), replace);
  return text;
}

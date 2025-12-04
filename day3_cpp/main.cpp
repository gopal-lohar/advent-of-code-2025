#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const char* test_input = "987654321111111\n\
811111111111119\n\
234234234234278\n\
818181911112111";

string read_file(const string& filename){
  ifstream file(filename);
  stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

int part_one(string data){
  istringstream stream(data);
  string line;
  int total_joltage = 0;

  while(getline(stream, line)){
    int winner = 0, runner_up = 0;
    for(int i = 0; i < line.length(); i++){
      char joltage = line[i];
      int part = joltage - '0';
      if (part > winner && i != line.length() - 1){
        runner_up = 0;
        winner = part;
      }else if (part > runner_up){
        runner_up = part;
      }
      // cout << "In for loop " << joltage << " " << part << endl;
    }

    total_joltage += ((winner * 10) + runner_up);
    cout << "joltage: " << ((winner * 10) + runner_up) << "total_joltage: " << total_joltage << "\n";
  }

  return total_joltage;
}

// wrong method for  part_two
// int part_two(string data){
//   istringstream stream(data);
//   string line;
//   long long total_joltage = 0;

//   while(getline(stream, line)){
//     int map[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

//     for(int i = 0; i < line.length(); i++){
//       char joltage = line[i];
//       int part = joltage - '0';
//       map[part-1]++;
//     }

//     cout << "B: Map: ";
//     for(int i = 0; i < 9; i++){
//       cout << map[i] << ", ";
//     }
//     cout << endl;

//     int remaining_digits = line.length() - 12;
//     for(int i = 0; i < 9; i++){
//       if(remaining_digits == 0){
//         map[i] = 0;
//       }else if(remaining_digits > map[i]){
//         remaining_digits -= map[i];
//       }else {
//         map[i] = remaining_digits;
//         remaining_digits = 0;
//       }
//     }

//     cout << "B: Map: ";
//     for(int i = 0; i < 9; i++){
//       cout << map[i] << ", ";
//     }
//     cout << endl;

//     string line_answer = line;
//     for(int i = 0; i < line.length(); i++){
//       char joltage = line[i];
//       int part = joltage - '0';
//       if (map[part-1] > 0){
//         line_answer.erase(i, 1);
//         map[part-1]--;
//       }
//     }

//     total_joltage += stoll(line_answer);
//     cout << "joltage: " << stoll(line_answer) << endl ;
//   }

//   return total_joltage;
// }


long long part_two(string data){
  istringstream stream(data);
  string line;
  long long total_joltage = 0;

  while(getline(stream, line)){
    string line_answer = line;

    int left_index = 0;
    int right_index = line.length() - 12;

    vector<bool> keep_mask(line.length(), true);
    for (int i = 0; i < line.length() - 12;){
      right_index = left_index + (line.length() - 12) - i;
      if(left_index > 12 + i - 1){
        for(int k = left_index; k < line.length(); k++){
          keep_mask[k] = false;
        }
        break;
      }
      
      int highest_index = left_index;
      int highest = line[highest_index] - '0';

      for(int j = left_index; j <= right_index; j++){
        int part = line[j] - '0';
        if(part > highest){
          highest = part;
          highest_index = j;
        }
      }

      for(int k = left_index; k < highest_index; k++){
        keep_mask[k] = false;
        i ++;
        // cout << "NEED TO REMOVE INDEX: " << k << endl;
        if(i >= line.length() - 12){
          break;
        }
      }
      // cout << "Highest between "<< left_index << " and " << right_index << " is " << highest << endl;
      int diff = highest_index  - left_index;
      left_index = highest_index + 1;
      // right_index+= diff + 1;
    }

    for(int k = line_answer.length() - 1; k >= 0; k--){
      if(!keep_mask[k]){
        line_answer.erase(k, 1); }
    }

    total_joltage += stoll(line_answer);
    cout << "joltage: " << stoll(line_answer) << "  answer: " << total_joltage << endl ;
  }

  return total_joltage;
}

int main(){
  string data = read_file("input.txt");
  // int answer_one = part_one(data);
  // cout << answer_one;

  long long answer_two = part_two(data);
  cout << answer_two;
}


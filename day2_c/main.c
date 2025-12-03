#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *read_file(char *filename){
  FILE *file = fopen(filename, "rb");
  if (!file){
    printf("couldn't open the file");
    return NULL;
  } 

  fseek(file, 0, SEEK_END);
  long length  = ftell(file);
  fseek(file, 0, SEEK_SET);

  char* buffer = malloc(length + 1);
  if (!buffer){
    fclose(file);
    printf("no buffer");
    return NULL;
  }

  fread(buffer, 1, length, file);
  buffer[length] = '\0';

  fclose(file);
  return buffer;  
}

// wrong function, not for strings, we need it for numbers
// bool isInvalid(char *productId){
//   int length = strlen(productId);
//   if (length == 0 || length % 2 != 0) return false;

//   int half_length = length / 2;

//   printf("\n the length is %d and the half length is %d of %s, with %s, cmp: %d \n", length, half_length, productId, productId + half_length, strncmp(productId, productId + half_length, half_length));

//   return strncmp(productId, productId + half_length, half_length) == 0 ? true : false;  
// }

int count_digits(long long num){
  if (num == 0) return 1;

  int count = 0;

  while (num != 0){
    num /= 10;
    count ++;
  }

  return count;
}

#define MAX_CAPACITY 100

int *get_factors_of_length(int target){
  int target_unmodified = target;
  int* factors = (int*)malloc(MAX_CAPACITY * sizeof(int));
  if (factors == NULL){
    return NULL;
  }

  int count = 0;

  factors[count] = 1;
  count++;

  if(target % 2 == 0 && target > 2){
    factors[count] = 2;
    count++;
  }

  for (int i = 3; i < target ; i ++) {
    // printf("In the loop with i=%d target=%d", i, target);
    if(target % i == 0){
      factors[count] = i;
      count ++;
    }
  }

  factors[count] = 0;

  return factors;
}

bool is_invalid_one(long long product_id){
  // printf("-------for %d------\n", product_id);
  int length = count_digits(product_id);
  // printf("---- no of digits %d\n", length);
  if (length == 0 || length % 2 != 0) return false;

  int half_length = length / 2;
  long long right_half = 0;
  long long left_half = product_id;

  for (int i = 0; i < half_length; i++) {
    int dec = 1;
    for (int j = 0; j < i; j++) {
        dec *= 10;
    }
    right_half += ((left_half % 10) * dec);
    left_half /= 10;
    // printf("-- iter: %d, left_half: %d, right_half: %d \n", i, left_half, right_half);
  }

  return left_half == right_half;
}

bool is_invalid_inner(int* factors, long long product_id, int length){
  int* current_factor = factors;

  if (length < 2) return false;
  
  while (*current_factor != 0){
    bool is_invalid = true;

    int first = 0;
    long long id = product_id;
    for (int i = 0; i < length; ){
      if(i==0){
        int dec = 1;
        for (int j = 0; j < *current_factor; j++) {
          first += ((id % 10) * dec);
          id /= 10;
          dec *= 10;
          i++;
        }
      }else{
        long long current = 0;
        int dec = 1;
        for (int j = 0; j < *current_factor; j++) {
          current += ((id % 10) * dec);
          id /= 10;
          dec *= 10;
          i++;
        }
        if (current != first){
          is_invalid = false;
        }
      }
    }

    if(is_invalid == true){
      return true;
    }
    current_factor++;
  }

  return false;
}

bool is_invalid_two(long long product_id){
  int length = count_digits(product_id);
  int* factors = get_factors_of_length(length);
  int* f = factors;
  bool is_invalid = is_invalid_inner(factors, product_id, length);
  free(factors);
  return is_invalid;
}

long long part1(char *input){
  long long answer = 0;
  
  char *rest_ranges = input;
  char *range = strtok_r(input, ",", &rest_ranges);


  while(range != NULL){
    char *rest_ids = range;

    // printf("range: %s ", range);

    char *productId = strtok_r(range, "-", &rest_ids);  
    long long startId = strtoll(productId, NULL, 10);
    productId = strtok_r(NULL, "-", &rest_ids);
    long long endId = strtoll(productId, NULL, 10);
    
    // printf("| %lld-%lld \n", startId, endId);
    for (long long id = startId; id <= endId; id++) {
      if (is_invalid_one(id) == 1){
        answer += id;
        // printf("ANWER inc: %lld\n", answer);
        // printf("%lld is invalid, now the answer is %lld\n", id, answer);
      }
    }
    
    range= strtok_r(NULL, ",", &rest_ranges);
  }

  printf("RETURNING ANSWER: %lld \n\n\n", answer);
  return answer;
}


long long part2(char *input){
  long long answer = 0;
  
  char *rest_ranges = input;
  char *range = strtok_r(input, ",", &rest_ranges);

  while(range != NULL){
    char *rest_ids = range;

    // printf("range: %s ", range);

    char *product_id = strtok_r(range, "-", &rest_ids);  
    long long start_id = strtoll(product_id, NULL, 10);
    product_id = strtok_r(NULL, "-", &rest_ids);
    long long end_id = strtoll(product_id, NULL, 10);
    
    // printf("| %lld-%lld \n", start_id, end_id);
    for (long long id = start_id; id <= end_id; id++) {
      if (is_invalid_two(id) == true){
        answer += id;
        // printf("ANWER inc: %lld\n", answer);
        // printf("%lld is invalid, now the answer is %lld\n", id, answer);
      }
    }
    
    range= strtok_r(NULL, ",", &rest_ranges);
  }

  printf("RETURNING ANSWER: %lld \n\n\n", answer);
  return answer;
}

int main(){
  char test_input[] = "11-22,95-115,998-1012,1188511880-1188511890,"
    "222220-222224,1698522-1698528,446443-446449,"
    "38593856-38593862,565653-565659,"
    "824824821-824824827,2121212118-2121212124";

  char *input = read_file("input.txt");

  // if(part1(testInput) != 1227775554){
  //   printf("part1 does not passes the test_input, it gives wrong answer: %lld", part1(testInput));
  // }else{
  //   printf("\n\n---PART-1 ANSWER:  %lld", part1(input));
  // }

  long long answer2 = part2(test_input);
  if(answer2 != 4174379265){
    printf("part2 does not passes the test_input, it gives wrong answer: %lld", answer2);
  }else{
    printf("---PART-2 ANSWER:  %lld", part2(input));
  }
  
  return 0;
}



import java.nio.file.Files;
import java.nio.file.Path;
import java.io.IOException;
import java.util.Arrays;

public class Main{
  public static void main(String[] args) {
    String testData = """
    123 328  51 64\s 
     45 64  387 23\s
      6 98  215 314
    *   +   *   + \s
    """;
    String data = readFile("./input.txt");
    System.out.println(partTwo(data));
  }

  public static String readFile(String filename){
    String data = "";
    try {
      data = Files.readString(Path.of(filename));
    } catch (IOException e) {
      System.err.println("Error reading file: " + e.getMessage());
    }
    return data;
  }
  
  public static long partOne(String data){
    String[] lines = data.strip().split("\n");
    int[][] problems = new int[lines.length-1][];
    for (int i = 0; i < lines.length - 1; i++) {
       problems[i] = Arrays.stream(lines[i].trim().split("\\s+")).mapToInt(Integer::parseInt).toArray();
    }

    String[] operations = lines[lines.length - 1].trim().split("\\s+"); 

    long answer = 0;
    for (int i = 0; i < operations.length; i++) {
      String operation = operations[i];

      if (operation.equals("*")){
        long product = 1;
        for(int j = 0; j < problems.length; j++){
          product *= problems[j][i];
        }
        // System.out.println(product);
        answer += product;
      } else if (operation.equals("+")){
        long sum = 0;
        for(int j = 0; j < problems.length; j++){
          sum += problems[j][i];
        }
        // System.out.println(sum);
        answer += sum;
      }
    }

    return answer;
  }
    
  
  public static long partTwo(String data){
    String[] lines = data.split("\n");

    String operations = lines[lines.length - 1];
    String[] numbers = java.util.Arrays.copyOf(lines, lines.length - 1);

    long answer = 0;

    for(int i = 0; i < operations.length();){
      int till = operations.length() - 1;
      for(int j = i+1; j < operations.length(); j++){
        if(operations.charAt(j) == '*' || operations.charAt(j)=='+'){
          till = j - 2;
          break;
        }
      }

      long product = 1;
      long sum = 0;
      System.out.println("i = " + i + " till = " + till + " length = " + operations.length());
      for(int x = i; x <= till; x++){
        int number = 0;
        int e = 0;
        for(int y = numbers.length - 1; y >= 0 ; y--){
          char c = numbers[y].charAt(x);
          if (Character.isDigit(c)) {
            int val = c - '0';
            int ten = (int) Math.pow(10, e);
            number += (val * ten);
            e++;
          }
        }
        if(operations.charAt(i) == '*' ){
          product *= number;
          System.out.println("ddddproduct " + number);
        }else if(operations.charAt(i)=='+'){
          sum += number;
          System.out.println("dddddsum " + number);
        }
      }

      
      if(operations.charAt(i) == '*' ){
        answer += product;
      }else if(operations.charAt(i)=='+'){
        answer += sum;
      }

      i = till + 2;

      System.out.println("in the loop at " + i + " sum " + sum + " product " + product);
    }
    return answer;
  }
}

import fs from 'node:fs';

const testInput = `L68
L30
R48
L5
R60
L55
L1
L99
R14
L82`

function readFile(path){
  try {
    return fs.readFileSync(path, 'utf8');
  } catch (err) {
    return "";
  }
}

function part1(input){
  let answer = 0;
  let knob = 50;

  input.split("\n").forEach(x => {
    const rotation = parseInt(x.slice(1));
    if (x[0] == "L"){
      knob -= rotation;
      while (knob < 0){
        knob = 100 + knob
      }
    }else{
      knob += rotation;
      knob = knob % 100;
    }

    if (knob == 0){
      answer ++;
    }
  });
  return answer
}

function part2(input){
  let answer = 0;
  let knob = 50;

  input.split("\n").forEach(x => {
    const rotation = parseInt(x.slice(1));
    if (Number.isNaN(rotation)){
      return;
    }
    if (x[0] == "L"){
      if (knob == 0){
          answer -= 1;
      }
      knob -= rotation;
      if (knob < 0){ 
        while (knob < 0){
          knob = 100 + knob
          answer += 1;
        }
      }
    }else{
      knob += rotation;
      if (knob > 99){ 
        while (knob > 99){
          knob = knob - 100;
          answer += 1;
        }
      }
      if (knob == 0){
        answer -= 1;
      }
    }

    
    if (knob === 0){
      answer += 1;
    }
    // console.log(`rotation: ${rotation}, dial: ${knob}, answer: ${answer}`)
  });
  return answer
}

const input = readFile("./input.txt");
if (part1(testInput) != 3){
  throw new Error("Part 1 does not pass the test case");
}else {
  console.log("Part 1 passes the test case");
}
console.log(`The answer for part 1 is ${part1(input)}`);
if (part2(testInput) != 6){
  throw new Error("Part 2 does not pass the test case");
}else {
  console.log("Part 2 passes the test case");
}
console.log(`The answer for part 2 is ${part2(input)}`);

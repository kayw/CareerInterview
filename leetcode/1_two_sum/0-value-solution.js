// smartstudy
/***
 *     [-3,-6,-1,-2,0,1,2,3,4,5,6]
 *         a + b = 0;
 *             */
'use strict';
function twoSum(inputArray) {
  const hashed = new Map();
  const visited = new Map();
  const result = [];
  inputArray.forEach((input, idx) => hashed.set(input, idx));
  for (let i = 0; i < inputArray.length; i++) {
    const target = 0 - inputArray[i];
    if (hashed.get(target) && hashed.get(target) !== i && !visited.get(target)) {
      visited.set(inputArray[i], true)
      result.push([target, inputArray[i]]);
    }
  }
  return result
}

// http://www.sigmainfy.com/blog/two-sum-problem-analysis-2-not-unique-no-duplicate.html
function twoSumSigmainfy(numbers, target) {
  const numIndexMap = new Map();
  numbers.forEach((num, idx) => numIndexMap.set(num, idx));
  const results = []
  for (let i = 0; i < numbers.length; i++) {
    const checkedNum = target - numbers[i];
    if (checkedNum === numbers[i]) {
      continue;
    }
    const checkedIndex = numIndexMap.get(checkedNum);
    if (checkedIndex !== undefined && checkedIndex >= i) {
      results.push([numbers[i], checkedNum]);
    }
  }
  return results;
}

console.log(twoSum([-3, -6, -1, -2, 0, 1, 2, 3, 4, 5, 6]));
//http://stackoverflow.com/questions/22395357/how-to-compare-two-arrays-are-equal-using-javascript-or-jquery
const sigmainfyResults = twoSumSigmainfy([-3, -6, -1, -2, 0, 1, 2, 3, 4, 5, 6], 0);
console.log('sigmainfy results', sigmainfyResults);
if (sigmainfyResults.toString() != [ [ -3, 3 ], [ -6, 6 ], [ -1, 1 ], [ -2, 2 ] ].toString()) {
  console.log('incorret');
}

'use strict';
//http://www.sigmainfy.com/blog/two-sum-problem-analysis-3-handling-duplicates-input.html
function twoSumDuplicate(nums, target) {
  const numMultiIndexMap = new Map();
  nums.forEach((num, index) => {
    if (numMultiIndexMap.get(num) !== undefined) {
      numMultiIndexMap.get(num).push(index);
    } else {
      numMultiIndexMap.set(num, [index]);
    }
  });
  const results = [];
  for (let i = 0; i < nums.length; i++) {
    const checkedNum = target - nums[i];
    if (numMultiIndexMap.get(checkedNum) !== undefined) {
      const checkedIndices = numMultiIndexMap.get(checkedNum);
      checkedIndices.forEach(ci => {
        if (ci > i) {
          results.push([i, ci]);
        }
      });
    }
  }
  return results;
}

let twoSumIndices = twoSumDuplicate([1,1,1,1], 2);
console.log(twoSumIndices)

twoSumIndices = twoSumDuplicate([2,7,3,6, 2,7], 9);
console.log(twoSumIndices)

/**
 * @param {string} s
 * @return {boolean}
 */

/**
 * Alternatively can use ES6 arrow function,
 * let checkIfPalindrome = (s) => { ... }
 */
var checkIfPalindrome = function(s) {
    let left = 0;
    let right = s.length - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}
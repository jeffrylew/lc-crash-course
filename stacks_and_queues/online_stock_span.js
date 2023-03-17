var StockSpanner = function() {
    this.stack = [];
};

/**
 * @param {number} price
 * @return {number}
 */
StockSpanner.prototype.next = function(price) {
    let ans = 1;

    while (this.stack.length && this.stack[this.stack.length - 1][0] <= price)
    {
        ans += this.stack.pop()[1];
    }

    this.stack.push([price, ans]);
    return ans;
};
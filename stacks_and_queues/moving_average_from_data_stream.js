/**
 * @param {number} size
 */
var MovingAverage = function(size)
{
    this.size         = size;
    this.windowSumDS1 = 0;
    this.countDS1     = 0;
    this.queueDS1     = [];
};

/**
 * Double-ended queue discussion solution
 * @param {number} val
 * @return {number}
 */
MovingAverage.prototype.nextDS1 = function(val)
{
    this.countDS1++;

    // Calculate the new sum by shifting the window
    this.queueDS1.push(val);
    const tail = this.countDS1 > this.size ? this.queueDS1.shift() : 0;

    this.windowSumDS1 = this.windowSumDS1 - tail + val;

    return this.windowSumDS1 * 1.0 / Math.min(this.size, this.countDS1);
};
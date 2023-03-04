/**
 * @param {number} size
 */
var MovingAverage = function(size)
{
    this.size         = size;
    this.windowSumDS1 = 0;
    this.countDS1     = 0;
    this.queueDS1     = [];

    this.windowSumDS2  = 0;
    this.countDS2      = 0;
    this.headDS2       = 0;
    this.circ_queueDS2 = Array(size).fill(0);
}

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

/**
 * Circular queue discussion solution
 * @param {number} val
 * @returns {number}
 */
MovingAverage.prototype.nextDS2 = function(val)
{
    this.countDS2++;

    // Calculate the new sum by shifting the window
    const tail = (this.headDS2 + 1) % this.size;
    this.windowSumDS2 = this.windowSumDS2 - this.circ_queueDS2[tail] + val;

    // Move on to the next head
    this.headDS2 = tail;
    this.circ_queueDS2[this.headDS2] = val;

    return this.windowSumDS2 * 1.0 / Math.min(this.size, this.countDS2);
};
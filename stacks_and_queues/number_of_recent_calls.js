var RecentCounter = function() {
    this.queue = [];
};

/**
 * @param {number} t
 * @returns {number}
 */
RecentCounter.prototype.ping = function(t) {
    while (this.queue.length && this.queue[0] < t - 3000)
    {
        this.queue.shift();
    }

    this.queue.push(t);
    return this.queue.length;
};
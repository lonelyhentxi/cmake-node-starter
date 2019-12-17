/// <reference path="./example.d.ts" />
const { Example } = require('bindings')('example.node');
const assert = require('assert');

const example = new Example(11);
assert.equal(example.GetValue(), 11);
console.info("example.GetValue() test pass.");
example.SetValue(19);
assert.equal(example.GetValue(), 19);
console.info("example.SetValue() test pass.");
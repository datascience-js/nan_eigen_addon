# nan_eigen_addon

Currently it's a POC that uses the [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) to perform linear algebra operations on matrices in js by creating a native addon to nodejs.

The current code uses two different approaches:

* Using the typed array mechanism in js.
 * TODO: check viability of this approach in terms of memory menegement ([afaik](https://github.com/nodejs/node/issues/883) after calling externalize transfers the responsibility of deleting the memory to the native addon which is bad).
* Using the [Smalloc](https://nodejs.org/api/smalloc.html) class which seems to work fine
 * Note: the js object should keep track of size allocated by smalloc.alloc (by e.g keeping `row`,`col` properties)

To run the example just:

```text
$ npm install
$ node-gyp rebuild
$ node ./
```
(based on [those](https://github.com/nodejs/node-addon-examples) examples)

Note: this addon's gyp file assumes that a folder `..\\eigen-eigen-10219c95fe65\\` exist and contains the above mentioned Eigen library files.

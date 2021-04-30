## Versioning policy

This project uses Semantic Versioning 2.0.0 (https://semver.org/).

Major version X MUST be incremented when affecting the public API, UI, and UX.

Minor version Y MUST be incremented when adding functionality without affecting the public API, UI, and major UX.

Build version Z must be incremented when solely fixing existing bugs.

Version is not incremented when changes do not alter computation results and only offer performance increases, readability, or adherence to project guidlines and policies, ie refactoring.

## Code policy

* ### Goals
	* The goals for this project are ordered to declare and define a comprimisation hierarchy.
		* Any and all goals will not be compromised for a lesser ranked goal.
		* Any and all goals will be compromised for a higher ranked goal.
	1. #### The lead focus is execution performance.
		1. Foremost, execution safety.
			* Results will be predictable and reliable.
		2. Secondarily, minimal computation time.
			* Results will be evaluated in minimal time.
		3. Finally, minimal storage cost.
			1. Foremost, execution requires a minimal use of internal memory.
			2. Secondarily, execution requires a minimal use of main memory.
			3. Finally, execution requires a minimal use of secondary memory.
	20. #### The secondary focus is independent code.
		1. Foremost, the code will be platform-independent.
		2. Secondarily, the code will not compomise its quality to service the short-comings of any compiler.
 		3. Finally, the code will have minimal code dependencies.
 	30. #### The tertiary focus is self-documenting code.
 	255. #### Finally, a minimal compilation time is appreciated—albiet, of least concern.

* ### Writing styles
	* The latest ISO standard C++20 is used.
	* The indentation style is Allman aka BSD style.
	* Ruler width is strictly 80 characters.
	* Adherence is to the [Core Guidelines].
* ### Naming conventions
	* Names use camel case.
	* Methods are verbs.
	* Object properties define its state.

// TODO: Set up typescript and port it to .ts
function validateBPF( filterExpr ) {
	var testFilter = Module.cwrap( "testFilter", "number", [ "string", "number", "number" ] );
	
	var maxErrLen = 1024;
	var errBuf = Module._malloc( maxErrLen+1 );
	var filterCompilationResult = testFilter( filterExpr, errBuf, 1024 );
	var errMessage = filterCompilationResult == 0 
		? "" 
		: Module.Pointer_stringify( errBuf );
	Module._free( errBuf );
	
	return {
		filter:	filterExpr,
		result: filterCompilationResult,
		error:	errMessage
	};
}

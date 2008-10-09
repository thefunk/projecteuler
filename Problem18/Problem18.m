#import <Foundation/Foundation.h>

static int FindMin(long *array, long size) {
	long currentMin = array[0];
	NSLog(@"%d", currentMin);
	for (long i = 1; i < size; i++) {
		NSLog(@"%d", array[i]);
		currentMin = MAX(currentMin, array[i]);
	}
	return currentMin;
}

static long SumOfShortestPath () {
	NSString *triangleText = [NSString stringWithContentsOfFile:[@"~/Downloads/triangle.txt" stringByExpandingTildeInPath]];
	NSArray *lines = [triangleText componentsSeparatedByString:@"\n"];
	long lineCount =[lines count];
	long *prevRow = calloc(lineCount, sizeof(long));
	long *curRow = calloc(lineCount, sizeof(long));
	
	for (long depth = 0; depth < lineCount; depth++) {
		NSString *line = [lines objectAtIndex:depth];
		
		NSArray *nums = [line componentsSeparatedByString:@" "];
		long index, count = [nums count];
		for (index = 0; index < count; index++) {
			long curVal = [[nums objectAtIndex:index] intValue];
			BOOL shouldCompare = NO;
			if (depth == 0) {
				curRow[index] = curVal;
			}
			if (index < count - 1) {
				curRow[index] = curVal + prevRow[index];
				shouldCompare = YES;
			}
			if (index > 0) {
				long possibleShortest = curVal + prevRow[index - 1];
				if (shouldCompare) {
					long curShortest = curRow[index];
					curRow[index] = MAX(possibleShortest, curShortest);
				} else {
					curRow[index] = possibleShortest;
				}
			}
		}
		memcpy(prevRow, curRow, lineCount * sizeof(long));
	}
	return FindMin(curRow, lineCount);
}

int main (int argc, const char * argv[]) {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSLog(@"%d", SumOfShortestPath());
    [pool drain];
    return 0;
}

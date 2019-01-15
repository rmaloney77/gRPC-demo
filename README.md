# gRPC Example

## Docker Deployment
docker build -t grpc-test .
docker run grpc-test

## Expected Output
Starting Server!
Username Available: 1
3 Statistics Returned

## For debug information when running unit tests
CTEST_OUTPUT_ON_FAILURE=1 make test

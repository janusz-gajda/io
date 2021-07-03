set src=%CD%
set dst=%CD%\_archive

rd %dst% /Q /S

mkdir "%dst%"

copy "%src%\src\optimized\imagefiltering.cpp"			"%dst%\imagefiltering.cpp"
copy "%src%\src\optimized\matrixmultiplication.cpp"		"%dst%\matrixmultiplication.cpp"
copy "%src%\src\optimized\histogramstretching.cpp"		"%dst%\histogramstretching.cpp"
copy "%src%\logs_Release\_HistogramStretching.txt"		"%dst%\_HistogramStretching.txt"
copy "%src%\logs_Release\_ImageFiltering.txt"			"%dst%\_ImageFiltering.txt"
copy "%src%\logs_Release\_MatrixMultiplication.txt"		"%dst%\_MatrixMultiplication.txt"
copy "%src%\logs_Debug\_HistogramStretching.txt"		"%dst%\D_HistogramStretching.txt"
copy "%src%\logs_Debug\_ImageFiltering.txt"				"%dst%\D_ImageFiltering.txt"
copy "%src%\logs_Debug\_MatrixMultiplication.txt"		"%dst%\D_MatrixMultiplication.txt"


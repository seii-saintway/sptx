# SPTX

This project is implemented using C++ and MFC (Microsoft Foundation Class) framework.

## Getting Started

The function `CMainFrame::Locate` is a private function that locates the target from the image captured by the camera. 

Firstly, the function calculates some parameters based on preset thresholds and the aperture area set in `pDoc->m_rtAperture`, and then processes the image to find the center position of the target.

Specifically, the function first converts the image data in `pImage` into grayscale and calculates the minimum and maximum grayscale values.

Then, for each row of grayscale values, the function calculates the mean and normalizes it. The relative position of the grayscale value in the image is then determined based on the normalized grayscale value.

Next, the function calculates the change in grayscale value `dI` for each row using first-order differentiation.

For the detected edges `iU1` and `iU2`, the function determines if the location is successful based on the preset thresholds `thY` and `thD`. If `iU2 - iU1` is greater than `thY` and there exists a grayscale value change greater than `thD` in the edge region, the location is considered successful.

Finally, the function returns the location result `pDoc->m_bSuccess`.

### Prerequisites

- Microsoft Visual Studio 2017 or later version.
- Basic understanding of C++ programming language.
- Familiarity with MFC framework.

### Installing

1. Clone the repository to your local machine using Git.
2. Open `SPTX.sln` solution file in Visual Studio.
3. Build the project by selecting Build -> Build Solution from the menu bar.
4. Run the project by selecting Debug -> Start Debugging from the menu bar.

## Contributing

Contributions to the project are welcome. To contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch for your changes.
3. Make your changes and commit them to your branch.
4. Push your changes to your forked repository.
5. Submit a pull request.

## License

This project is licensed under the Apache License - see the LICENSE file for details.

## Acknowledgments

- The project was developed as part of a course project at XYZ University.

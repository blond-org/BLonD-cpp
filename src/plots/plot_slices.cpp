#include <blond/plots/plot_slices.h>
#include <blond/python.h>
#include <blond/utilities.h>

void plot_beam_profile(Slices *Slices,
                       int counter,
                       std::string style,
                       std::string dirname)
{
    // python::initialize();
    python::import();
    auto pFunc = python::import("plot_slices", "plot_beam_profile");

    auto pBinCenters = python::convert_double_array(Slices->bin_centers.data(),
                       Slices->bin_centers.size());
    auto pNMacropaticles = python::convert_int_array(Slices->n_macroparticles.data(),
                           Slices->n_macroparticles.size());
    auto pCounter = python::convert_int(counter);
    auto pStyle = python::convert_string(style);
    auto pDirname = python::convert_string(dirname);

    auto ret = PyObject_CallFunctionObjArgs(pFunc, pBinCenters, pNMacropaticles,
                                            pCounter, pStyle,  pDirname,
                                            NULL);
    assert(ret);
    // python::finalize();
}


void plot_beam_profile_derivative(Slices *Slices,
                                  int counter,
                                  std::string style,
                                  std::string dirname,
                                  string_vector_t modes)
{
    python::import();
    auto pFunc = python::import("plot_slices", "plot_beam_profile_derivative");

    f_vector_2d_t x(modes.size(), f_vector_t());
    f_vector_2d_t derivative(modes.size(), f_vector_t());
    for (uint i = 0; i < modes.size(); i++) {
        Slices->beam_profile_derivative(x[i], derivative[i], modes[i]);
        // util::dump(x[i], "x\n", 5);
        // util::dump(derivative[i], "derivative\n");
    }

    auto pX = python::convert_double_2d_array(x);
    auto pDerivative = python::convert_double_2d_array(derivative);

    auto pModes = python::convert_string_array(modes.data(), modes.size());
    auto pCounter = python::convert_int(counter);
    auto pStyle = python::convert_string(style);
    auto pDirname = python::convert_string(dirname);

    auto ret = PyObject_CallFunctionObjArgs(pFunc, pX, pDerivative, pCounter,
                                            pStyle, pDirname, pModes, NULL);
    assert(ret);
}

void plot_beam_spectrum(Slices *Slices, int counter,
                        std::string style,
                        std::string dirname)
{

    python::import();
    auto pFunc = python::import("plot_slices", "plot_beam_spectrum");

    auto pBeamSpectrumFreq = python::convert_double_array(
                                 Slices->fBeamSpectrumFreq.data(),
                                 Slices->fBeamSpectrumFreq.size());
    auto pBeamSpectrum = python::convert_complex_array(
                             Slices->fBeamSpectrum.data(),
                             Slices->fBeamSpectrum.size());


    auto pCounter = python::convert_int(counter);
    auto pStyle = python::convert_string(style);
    auto pDirname = python::convert_string(dirname);

    auto ret = PyObject_CallFunctionObjArgs(pFunc, pBeamSpectrumFreq,
                                            pBeamSpectrum, pCounter, pStyle,
                                            pDirname, NULL);
    assert(ret);

}
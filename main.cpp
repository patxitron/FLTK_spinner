/**
 * @file
 * 
 * Program entry point.
 */

#define _BSD_SOURCE

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>
#include "uintspinner.hpp"
#include "util.hpp"

static void salir(Fl_Widget*,void*) { std::exit(0); }

static void spnrcbk(Fl_Widget*,void*)
{
    std::cout << "spnrcbk()" << std::endl;
}

int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(720,480);
    Fl_Button *button = new Fl_Button(10, 390, 700, 80, "SALIR");
#ifdef USE_UINT_SPINNER
    patxitron::UintSpinner* spinner = new  patxitron::UintSpinner(10, 10, 0, 244, 2);
    spinner->callback(&spnrcbk);
#else // !USE_UINT_SPINNER
    std::vector<std::unique_ptr<patxitron::Spinner>> spinners;
    for (size_t i = 0; i < 4; i++) {
        spinners.emplace_back(new patxitron::Spinner(10 + i * patxitron::Spinner::WIDTH, 10, 2));
        spinners.back()->callback(&spnrcbk);
    }
#endif // USE_UINT_SPINNER
    button->callback(&salir);
    button->labelsize(60);
    button->box(FL_BORDER_FRAME);
    button->color(FL_RED);
    button->labelcolor(FL_RED);
    window->color(FL_BLACK, FL_RED);
    window->end();
    window->show(argc, argv);
    return Fl::run();
}

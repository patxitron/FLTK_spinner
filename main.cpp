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
    patxitron::UintSpinner* spinner = new  patxitron::UintSpinner(10, 10, 0, 244, 2);
//    patxitron::Spinner* spinner = new patxitron::Spinner(10, 10, 2);
    spinner->callback(&spnrcbk);
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

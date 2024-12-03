#include <float.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "calculate.h"

GtkWidget *entry1, *entry2, *operator_entry, *result_label;

// Callback for the "Calculate" button
void on_calculate_clicked(GtkWidget *widget, gpointer data) {
    const char *num1_text = gtk_entry_get_text(GTK_ENTRY(entry1));
    const char *num2_text = gtk_entry_get_text(GTK_ENTRY(entry2));
    const char *operator_text = gtk_entry_get_text(GTK_ENTRY(operator_entry));

    // Convert inputs to numbers and operator
    double num1 = atof(num1_text);
    double num2 = atof(num2_text);
    char operator = operator_text[0]; // Get first character as operator

    // Perform calculation
    double result = calculate(num1, num2, operator);

    // Update the result label
    char result_text[100];
    snprintf(result_text, sizeof(result_text), "Result: %.2lf", result);
    gtk_label_set_text(GTK_LABEL(result_label), result_text);
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *calculate_button;
    GtkCssProvider *css_provider;
    GdkScreen *screen;

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create main application window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Load custom CSS file for styling
    css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "style.css", NULL);
    screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Create a grid layout for the calculator
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create input fields and labels
    GtkWidget *label1 = gtk_label_new("Operand 1:");
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 1, 1);
    entry1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry1, 1, 0, 1, 1);
    gtk_widget_set_hexpand(entry1, TRUE);
    gtk_widget_set_vexpand(entry1, TRUE);

    GtkWidget *label2 = gtk_label_new("Operand 2:");
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 1, 1, 1);
    entry2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 1, 1, 1);
    gtk_widget_set_hexpand(entry2, TRUE);
    gtk_widget_set_vexpand(entry2, TRUE);

    GtkWidget *label3 = gtk_label_new("Operator (+, -, *, /):");
    gtk_grid_attach(GTK_GRID(grid), label3, 0, 2, 1, 1);
    operator_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), operator_entry, 1, 2, 1, 1);
    gtk_widget_set_hexpand(operator_entry, TRUE);
    gtk_widget_set_vexpand(operator_entry, TRUE);

    // Create the calculate button
    calculate_button = gtk_button_new_with_label("Calculate");
    gtk_grid_attach(GTK_GRID(grid), calculate_button, 0, 3, 2, 1);
    g_signal_connect(calculate_button, "clicked", G_CALLBACK(on_calculate_clicked), NULL);
    gtk_widget_set_hexpand(calculate_button, TRUE);
    gtk_widget_set_vexpand(calculate_button, TRUE);

    // Create a result label
    result_label = gtk_label_new("Result: ");
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 4, 2, 1);
    gtk_widget_set_hexpand(result_label, TRUE);
    gtk_widget_set_vexpand(result_label, TRUE);

    // Show all widgets
    gtk_widget_show_all(window);

    // Run the main GTK loop
    gtk_main();

    return 0;
}
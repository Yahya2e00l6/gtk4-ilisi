
#include "activates.h"

#include "button.h"
#include "containers.h"
#include "input.h"
#include "widgets.h"

typedef struct {
	GtkWidget *entry;
	GtkWidget *dropdown;
} ActiveUi;

static const char *get_selected_text(GtkDropDown *dropdown) {
	guint selected = gtk_drop_down_get_selected(dropdown);
	GListModel *model = gtk_drop_down_get_model(dropdown);
	if (GTK_IS_STRING_LIST(model)) {
		return gtk_string_list_get_string(GTK_STRING_LIST(model), selected);
	}
	return NULL;
}

static void submit(ActiveUi *ui) {
	if (!ui) {
		return;
	}

	const char *text = NULL;
	if (ui->entry) {
		text = gtk_editable_get_text(GTK_EDITABLE(ui->entry));
	}

	const char *selected = NULL;
	if (ui->dropdown) {
		selected = get_selected_text(GTK_DROP_DOWN(ui->dropdown));
	}

	g_print("Entry: %s | Selected: %s\n", text ? text : "", selected ? selected : "");
}

static void on_submit_clicked(GtkButton *btn, gpointer user_data) {
	(void)btn;
	submit((ActiveUi *)user_data);
}

static void on_entry_activate(GtkEntry *entry, gpointer user_data) {
	(void)entry;
	submit((ActiveUi *)user_data);
}

void on_active(GtkApplication *app, gpointer user_data) {
	(void)user_data;

	Window window_config = {
		.title = "GTK4 App",
		.width = 800,
		.height = 600,
		.maximized = false,
	};

	GtkWidget *window = create_window(app, &window_config);

	Grid grid_config = {
		.column_spacing = 12,
		.row_spacing = 12,
		.column_homogeneous = false,
		.row_homogeneous = false,
		.halign = GTK_ALIGN_FILL,
		.valign = GTK_ALIGN_START,
		.hexpand = true,
		.vexpand = true,
		.margin_top = 12,
		.margin_bottom = 12,
		.margin_start = 12,
		.margin_end = 12,
	};

	GtkWidget *grid = create_grid(&grid_config);
	gtk_window_set_child(GTK_WINDOW(window), grid);

	ActiveUi *ui = g_new0(ActiveUi, 1);
	g_object_set_data_full(G_OBJECT(window), "active-ui", ui, g_free);

	input_config entry_config = {
		.placeholder = "Type something...",
		.default_text = "",
		.css_class = NULL,
		.is_password = false,
		.max_length = 0,
		.is_editable = true,
		.purpose = GTK_INPUT_PURPOSE_FREE_FORM,
		.xalign = 0.0f,
		.has_frame = true,
		.halign = GTK_ALIGN_FILL,
		.valign = GTK_ALIGN_CENTER,
		.hexpand = true,
		.margin_top = 0,
		.margin_bottom = 0,
		.margin_start = 0,
		.margin_end = 0,
		.on_change = NULL,
		.on_activate = on_entry_activate,
		.user_data = ui,
	};

	ui->entry = create_input(&entry_config);

	static const char *options[] = {"Option A", "Option B", "Option C", NULL};
	select_config dropdown_config = {
		.options = options,
		.selected_index = 0,
		.css_class = NULL,
		.has_entry = false,
		.id_column = NULL,
		.halign = GTK_ALIGN_FILL,
		.valign = GTK_ALIGN_CENTER,
		.hexpand = true,
		.vexpand = false,
		.margin_top = 0,
		.margin_bottom = 0,
		.margin_start = 0,
		.margin_end = 0,
		.on_change = my_select_handler,
		.user_data = NULL,
	};

	ui->dropdown = create_select(&dropdown_config);

	ButtonConfig button_config = {
		.label = "Submit",
		.icon = NULL,
		.css_class = NULL,
		.has_frame = true,
		.use_underline = false,
		.halign = GTK_ALIGN_START,
		.valign = GTK_ALIGN_CENTER,
		.hexpand = false,
		.vexpand = false,
		.margin_top = 0,
		.margin_bottom = 0,
		.margin_start = 0,
		.margin_end = 0,
		.width = 0,
		.height = 0,
		.on_click = on_submit_clicked,
		.user_data = ui,
	};

	GtkWidget *submit_btn = create_button(&button_config);

	add_to_grid(grid, ui->entry, &(GridChild){.column = 0, .row = 0, .width = 2, .height = 1});
	add_to_grid(grid, ui->dropdown, &(GridChild){.column = 0, .row = 1, .width = 2, .height = 1});
	add_to_grid(grid, submit_btn, &(GridChild){.column = 0, .row = 2, .width = 1, .height = 1});

	gtk_window_present(GTK_WINDOW(window));
}


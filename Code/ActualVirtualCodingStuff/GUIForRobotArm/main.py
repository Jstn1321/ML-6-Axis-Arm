import dearpygui.dearpygui as dpg
import time
import threading
from sys import platform

dpg.create_context()


path = "bog/liveTest/filename.jpg"


times = [0]
values = [[0] for _ in range(6)]
last_values = [0] * 6
max_points = 100
rate_of_change = [0] * 6  # To store the instantaneous rate of change for each slider

width, height, channels, data = dpg.load_image(path)

with dpg.texture_registry():
    texture_id = dpg.add_static_texture(width, height, data)

def update_plot(slider_index, sender, app_data):
    last_values[slider_index] = app_data


def print_values():
    global rate_of_change

    if len(times) > 2:
        # Calculate the instantaneous rate of change for each slider
        rate_of_change[0] = (values[0][-1] - values[0][-3]) / (times[-1] - times[-3])
        rate_of_change[1] = (values[1][-1] - values[1][-3]) / (times[-1] - times[-3])
        rate_of_change[2] = (values[2][-1] - values[2][-3]) / (times[-1] - times[-3])
        rate_of_change[3] = (values[3][-1] - values[3][-3]) / (times[-1] - times[-3])
        rate_of_change[4] = (values[4][-1] - values[4][-3]) / (times[-1] - times[-3])
        rate_of_change[5] = (values[5][-1] - values[5][-3]) / (times[-1] - times[-3])

        # Update the text on the GUI
        dpg.set_value("rate_of_change_0", f"Axis 1 Instantaneous Rate of Change: {rate_of_change[0]:.2f}")
        dpg.set_value("rate_of_change_1", f"Axis 2 Instantaneous Rate of Change: {rate_of_change[1]:.2f}")
        dpg.set_value("rate_of_change_2", f"Axis 3 Instantaneous Rate of Change: {rate_of_change[2]:.2f}")
        dpg.set_value("rate_of_change_3", f"Axis 4 Instantaneous Rate of Change: {rate_of_change[3]:.2f}")
        dpg.set_value("rate_of_change_4", f"Axis 5 Instantaneous Rate of Change: {rate_of_change[4]:.2f}")
        dpg.set_value("rate_of_change_5", f"Axis 6 Instantaneous Rate of Change: {rate_of_change[5]:.2f}")


def continuous_update():
    while dpg.is_dearpygui_running():
        current_time = time.time() - start_time

        if len(times) == max_points:
            times.pop(0)

        times.append(current_time)

        for i in range(6):
            if len(values[i]) == max_points:
                values[i].pop(0)
            values[i].append(last_values[i])

        # Batch update all series
        dpg.configure_item("plot_series_0", x=times, y=values[0])
        dpg.configure_item("plot_series_1", x=times, y=values[1])
        dpg.configure_item("plot_series_2", x=times, y=values[2])
        dpg.configure_item("plot_series_3", x=times, y=values[3])
        dpg.configure_item("plot_series_4", x=times, y=values[4])
        dpg.configure_item("plot_series_5", x=times, y=values[5])

        if current_time > 10:
            dpg.set_axis_limits("x_axis", current_time - 10, current_time)
        else:
            dpg.set_axis_limits("x_axis", 0, 10)

        print_values()  # Print values of all sliders
        time.sleep(0.04)  # Update every 0.04 seconds


start_time = time.time()


def picture_Callback():
    print("Taking picture")


def id_Callback():
    print("Identifying")

def sort_Callback():
    print("Sorting")


with dpg.window(tag="Primary Window"):
    with dpg.tab_bar():
        with dpg.tab(label='Automatic'):
            with dpg.group(label='pic', horizontal=True):
                    dpg.add_button(label="Take Picture", callback=picture_Callback)
                    dpg.add_image(texture_id)
            dpg.add_button(label="Identify Object", callback=id_Callback)
            dpg.add_button(label="Begin Sorting Object", callback=sort_Callback)


        with dpg.tab(label='Manual'):
            with dpg.plot(label="Motor Values", height=400, width=875):
                dpg.add_plot_legend()
                x_axis = dpg.add_plot_axis(dpg.mvXAxis, label="Time (s)", tag="x_axis")
                y_axis = dpg.add_plot_axis(dpg.mvYAxis, label="Degrees", tag="y_axis")

                dpg.add_line_series(times, values[0], label="Axis 1", parent=y_axis, tag="plot_series_0")
                dpg.add_line_series(times, values[1], label="Axis 2", parent=y_axis, tag="plot_series_1")
                dpg.add_line_series(times, values[2], label="Axis 3", parent=y_axis, tag="plot_series_2")
                dpg.add_line_series(times, values[3], label="Axis 4", parent=y_axis, tag="plot_series_3")
                dpg.add_line_series(times, values[4], label="Axis 5", parent=y_axis, tag="plot_series_4")
                dpg.add_line_series(times, values[5], label="Axis 6", parent=y_axis, tag="plot_series_5")

                dpg.set_axis_limits(y_axis, -10, 370)

            # Add text to display the instantaneous rate of change
            with dpg.group(label='1-3', horizontal=True):
                dpg.add_text("Axis 1 Instantaneous Rate of Change: 0.00", tag="rate_of_change_0")
                dpg.add_spacer(width=10)
                dpg.add_text("Axis 3 Instantaneous Rate of Change: 0.00", tag="rate_of_change_2")
                dpg.add_spacer(width=10)
                dpg.add_text("Axis 5 Instantaneous Rate of Change: 0.00", tag="rate_of_change_4")
            with dpg.group(label='4-6', horizontal=True):
                dpg.add_text("Axis 2 Instantaneous Rate of Change: 0.00", tag="rate_of_change_1")
                dpg.add_spacer(width=10)
                dpg.add_text("Axis 4 Instantaneous Rate of Change: 0.00", tag="rate_of_change_3")
                dpg.add_spacer(width=10)
                dpg.add_text("Axis 6 Instantaneous Rate of Change: 0.00", tag="rate_of_change_5")

            dpg.add_text("Shoulder Motors")
            dpg.add_slider_int(tag="slider_0", label="Axis 1", default_value=0, min_value=0, max_value=360,
                               callback=lambda s, a: update_plot(0, s, a))
            dpg.add_slider_int(tag="slider_1", label="Axis 2", default_value=0, min_value=0, max_value=360,
                               callback=lambda s, a: update_plot(1, s, a))
            dpg.add_text("Elbow Motors")
            dpg.add_slider_int(tag="slider_2", label="Axis 3", default_value=0, min_value=0, max_value=360,
                               callback=lambda s, a: update_plot(2, s, a))
            dpg.add_slider_int(tag="slider_3", label="Axis 4", default_value=0, min_value=0, max_value=360,
                               callback=lambda s, a: update_plot(3, s, a))
            dpg.add_text("Hand Motors")
            dpg.add_slider_int(tag="slider_4", label="Axis 5", default_value=0, min_value=0, max_value=360,
                               callback=lambda s, a: update_plot(4, s, a))
            dpg.add_slider_int(tag="slider_5", label="Axis 6", default_value=0, min_value=0, max_value=360,
                               callback=lambda s, a: update_plot(5, s, a))

dpg.create_viewport(title='Robot Arm V1', width=1400, height=800)
dpg.setup_dearpygui()
dpg.show_viewport()

# Start the continuous update in a separate thread
threading.Thread(target=continuous_update, daemon=True).start()

dpg.set_primary_window("Primary Window", True)
dpg.start_dearpygui()
dpg.destroy_context()

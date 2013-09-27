import sys
sys.path.append(  "/usr/lib/python3/dist-packages" )
print (sys.path)

import bpy
import math
import httplib2


class MultiGCSlive(bpy.types.Operator):
    '''Operator which changes selected objects location'''
    bl_idname = "wm.multigcs_changes_location"
    bl_label = "multigcs changes location"

    _timer = None

    def modal(self, context, event):
        if event.type == 'ESC':
            return self.cancel(context)

        if event.type == 'TIMER':

            URL = "http://127.0.0.1:8080/blender.txt"
            h = httplib2.Http(".cache")
            resp, content = h.request(URL, "GET")

            Coords=[0.0,0.0,0.0,0.0,0.0,0.0] # Inicial location
            CoordsNumber=6
            for i in range(CoordsNumber):
                Coords[i] = Coords[i] + (float)(content.split()[i])
            objects = context.selected_objects
            for object in objects:
                object.rotation_euler[0] = Coords[1] * 3.14159 / 180.0 * -1
                object.rotation_euler[1] = Coords[0] * 3.14159 / 180.0
                object.rotation_euler[2] = Coords[2] * 3.14159 / 180.0 * -1

                object.location.x = Coords[3] * -200.0
                object.location.y = Coords[4] * 200.0
                object.location.z = Coords[5] / 40.0



        return {'PASS_THROUGH'}

    def execute(self, context):
        context.window_manager.modal_handler_add(self)
        self._timer = context.window_manager.event_timer_add(0.1, context.window)
        return {'RUNNING_MODAL'}

    def cancel(self, context):
        context.window_manager.event_timer_remove(self._timer)
        return {'CANCELLED'}


def register():
    bpy.utils.register_class(MultiGCSlive)


def unregister():
    bpy.utils.unregister_class(MultiGCSlive)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.wm.multigcs_changes_location()
    

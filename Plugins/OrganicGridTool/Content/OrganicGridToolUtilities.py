import unreal

class OrganicGridToolUtilities:

    ORGANIC_GRID_TOOL_MESH_ACTOR_PATH = "D:/GitHub/UnrealEngineTools/Plugins/OrganicGridTool/Content/Actors/OrganicGridMeshActor.uasset"

    @classmethod

    @classmethod
    def spawn_organic_grid_tooL_mesh_actor(cls):
        actor = unreal.EditorLevelLibrary.spawn_actor_from_class()
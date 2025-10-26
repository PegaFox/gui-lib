const std = @import("std");

const version = std.SemanticVersion{.major = 1, .minor = 0, .patch = 0};

pub fn build(b: *std.Build) void {
  const target = b.standardTargetOptions(.{});
  const optimize = b.standardOptimizeOption(.{});
    
  const srcMod = b.addModule("gui-lib", .{
    .target = target,
    .optimize = optimize,
    .link_libc = true,
    .link_libcpp = true,
  });

  srcMod.addIncludePath(.{.src_path = .{.owner = b, .sub_path = "include/"}});
  srcMod.addCSourceFiles(.{
    // When provided, `files` are relative to `root` rather than the
    // package that owns the `Compile` step.
    //root: ?LazyPath = null,
    .files = &.{
      // main lib
      "src/gui_element.cpp",
      "src/window.cpp",
      "src/vertex_array.cpp",
      "src/paragraph.cpp",
      "src/button.cpp",
      "src/selection.cpp",
      "src/slider.cpp",
      "src/drag_field.cpp",
      "src/drag_box.cpp",

      // C declarations
      "src/c/gui_element.cpp",
      "src/c/window.cpp",
      "src/c/vertex_array.cpp",
      "src/c/paragraph.cpp",
      "src/c/button.cpp",
      "src/c/slider.cpp",
      "src/c/drag_field.cpp",
      "src/c/drag_box.cpp",
    },
    //flags: []const []const u8 = &.{},
    // By default, determines language of each file individually based on its file extension
    .language = .cpp,
  });

  const gui_lib = b.addLibrary(.{
    //linkage: std.builtin.LinkMode = .static,
    .name = "gui-lib",
    .root_module = srcMod,
    .version = version,
  });

  gui_lib.installHeadersDirectory(.{.src_path = .{.owner = b, .sub_path = "include/"}}, ".", .{.include_extensions = null});

  // This declares intent for the executable to be installed into the
  // standard location when the user invokes the "install" step (the default
  // step when running `zig build`).
  b.installArtifact(gui_lib);

  const exe_unit_tests = b.addTest(.{
    .root_module = srcMod,
  });

  const run_exe_unit_tests = b.addRunArtifact(exe_unit_tests);

  // Similar to creating the run step earlier, this exposes a `test` step to
  // the `zig build --help` menu, providing a way for the user to request
  // running the unit tests.
  const testStep = b.step("test", "Run unit tests");
  testStep.dependOn(&run_exe_unit_tests.step);

  // Fast error checking
  const exeCheck = b.addLibrary(.{
    .name = "gui-lib",
    .root_module = srcMod,
    .version = version,
  });

  const check = b.step("check", "Scan syntax for errors");
  check.dependOn(&exeCheck.step);
}


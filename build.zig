const std = @import("std");

const version = struct {
    const major = 1;
    const minor = 16;
};

pub fn build(b: *std.Build) void {
    const optimize = b.standardOptimizeOption(.{ .preferred_optimize_mode = .ReleaseFast });
    const target = b.standardTargetOptions(.{});

    const config = b.addConfigHeader(
        .{ .style = .blank, .include_path = "config.h" },
        .{
            .CONFIG_VERSION_MAJOR = version.major,
            .CONFIG_VERSION_MINOR = version.minor,
        },
    );

    const lib = b.addLibrary(.{
        .name = "ubloxcfg",
        .root_module = b.createModule(.{ .target = target, .optimize = optimize }),
    });
    lib.addCSourceFiles(.{
        .root = b.path("src"),
        .files = &.{
            "ff_crc.c",
            "ff_debug.c",
            "ff_epoch.c",
            "ff_nmea.c",
            "ff_novatel.c",
            "ff_parser.c",
            "ff_port.c",
            "ff_rtcm3.c",
            "ff_rx.c",
            "ff_spartn.c",
            "ff_stuff.c",
            "ff_time.c",
            "ff_trafo.c",
            "ff_ubx.c",
            "ubloxcfg.c",
            "ubloxcfg_gen.c",
        },
        .flags = &CFLAGS,
    });
    lib.addConfigHeader(config);
    lib.addIncludePath(b.path("include"));
    lib.installHeadersDirectory(b.path("include"), "ubloxcfg", .{});
    lib.linkLibC();
    b.installArtifact(lib);
}

const CFLAGS = .{
    "-Wall",
    "-Wextra",
    "-Wmissing-prototypes",
    "-Wmissing-declarations",
    "-Wformat=2",
    "-Wold-style-definition",
    "-Wstrict-prototypes",
    "-Wpointer-arith",
};

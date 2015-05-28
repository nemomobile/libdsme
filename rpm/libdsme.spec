Name:       libdsme

Summary:    DSME dsmesock dynamic library
Version:    0.63.2
Release:    0
Group:      System/System Control
License:    LGPL
URL:        https://github.com/nemomobile/libdsme
Source0:    %{name}-%{version}.tar.bz2
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(check)

%description
This package contains dynamic libraries for programs that communicate with the
Device State Management Entity.


%package devel
Summary:    Development files for dsme
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
This package contains headers and static libraries needed to develop programs
that want to communicate with the Device State Management Entity.


%package tests
Summary:    Test suite for dsme
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description tests
This package contains test suite for libdsme.


%prep
%setup -q -n %{name}-%{version}

%build
unset LD_AS_NEEDED
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/libdsme.so.*
%{_libdir}/libdsme_dbus_if.so.*
%{_libdir}/libthermalmanager_dbus_if.so.*
%doc debian/copyright
%doc COPYING

%files devel
%defattr(-,root,root,-)
%{_includedir}/dsme/*
%{_libdir}/libdsme.so
%{_libdir}/libdsme_dbus_if.so
%{_libdir}/libthermalmanager_dbus_if.so
%{_libdir}/pkgconfig/*

%files tests
%defattr(-,root,root,-)
/opt/tests/libdsme/*

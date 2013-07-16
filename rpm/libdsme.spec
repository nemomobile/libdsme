# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.27
# 

Name:       libdsme

# >> macros
# << macros

Summary:    DSME dsmesock dynamic library
Version:    0.61.7
Release:    0
Group:      System/System Control
License:    LGPL
URL:        https://github.com/nemomobile/libdsme
Source0:    %{name}-%{version}.tar.bz2
Source100:  libdsme.yaml
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

# >> setup
# << setup

%build
unset LD_AS_NEEDED
# >> build pre
# << build pre


make %{?jobs:-j%jobs}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%make_install

# >> install post


# << install post

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
# >> files
%{_libdir}/libdsme.so.0.2.0
%{_libdir}/libdsme_dbus_if.so.0.2.0
%{_libdir}/libthermalmanager_dbus_if.so.0.2.0
%doc debian/copyright
%doc COPYING
# << files

%files devel
%defattr(-,root,root,-)
# >> files devel
%{_includedir}/dsme/*
%{_libdir}/libdsme.so
%{_libdir}/libdsme_dbus_if.so
%{_libdir}/libthermalmanager_dbus_if.so
%{_libdir}/pkgconfig/*
# << files devel

%files tests
%defattr(-,root,root,-)
# >> files tests
/opt/tests/libdsme/*
# << files tests

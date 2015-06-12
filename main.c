/* Carbon includes everything necessary for Accessibilty API */
#include <Carbon/Carbon.h>

static bool hasAccessibilityAPIAuthorization ()
{
    if (AXAPIEnabled() != 0) {
        return true;
    }

    if (AXIsProcessTrusted() != 0) {
        return true;
    }

    return false;
}

/**
 * Give the user 5 seconds to switch to window
 * they want locked
 */
static void waitForFiveSeconds ()
{
    int i;

    printf("Select the window you want to lock:\n");

    for (i = 0; i < 5; i++) {
        sleep(1);
        printf("%d", i + 1);
        if (i < 4) {
            printf("...");
            fflush(stdout);
        } else {
            printf("\n");
        }
    }
}


static AXUIElementRef getFrontMostApp ()
{
    pid_t pid;
    ProcessSerialNumber psn;

    GetFrontProcess(&psn);
    GetProcessPID(&psn, &pid);
    return AXUIElementCreateApplication(pid);
}


int main (
    int argc,
    char ** argv
) {
    int i;
    AXValueRef temp;

    AXValueRef pos1;
    AXValueRef pos2;
    AXValueRef pos3;

    AXValueRef size1;
    AXValueRef size2;
    AXValueRef size3;

    CGSize windowSize1;
    CGSize windowSize2;
    CGSize windowSize3;

    CGPoint windowPosition1;
    CGPoint windowPosition2;
    CGPoint windowPosition3;

    CFStringRef windowTitle1;
    CFStringRef windowTitle2;
    CFStringRef windowTitle3;

    AXUIElementRef app1;
    AXUIElementRef app2;
    AXUIElementRef app3;

    AXUIElementRef frontWindow1;
    AXUIElementRef frontWindow2;
    AXUIElementRef frontWindow3;

    if (!hasAccessibilityAPIAuthorization()) {
        printf("Can't use accessibility API!\n");
        return 1;
    }

    waitForFiveSeconds();

    app1 = getFrontMostApp();

    waitForFiveSeconds();

    app2 = getFrontMostApp();

    waitForFiveSeconds();

    app3 = getFrontMostApp();

    /**
     * Get app1's front most window.
     */
    AXUIElementCopyAttributeValue(
        app1, kAXFocusedWindowAttribute, (CFTypeRef *)&frontWindow1
    );

    /* Get the title of the window */
    AXUIElementCopyAttributeValue(
        frontWindow1, kAXTitleAttribute, (CFTypeRef *)&windowTitle1
    );

    /* Get the window size and position */
    AXUIElementCopyAttributeValue(
        frontWindow1, kAXSizeAttribute, (CFTypeRef *)&temp
    );
    AXValueGetValue(temp, kAXValueCGSizeType, &windowSize1);
    CFRelease(temp);

    AXUIElementCopyAttributeValue(
        frontWindow1, kAXPositionAttribute, (CFTypeRef *)&temp
    );
    AXValueGetValue(temp, kAXValueCGPointType, &windowPosition1);
    CFRelease(temp);


    /**
     * Get app2's front most window.
     */
    AXUIElementCopyAttributeValue(
        app2, kAXFocusedWindowAttribute, (CFTypeRef *)&frontWindow2
    );

    /* Get the title of the window */
    AXUIElementCopyAttributeValue(
        frontWindow2, kAXTitleAttribute, (CFTypeRef *)&windowTitle2
    );

    /* Get the window size and position */
    AXUIElementCopyAttributeValue(
        frontWindow2, kAXSizeAttribute, (CFTypeRef *)&temp
    );
    AXValueGetValue(temp, kAXValueCGSizeType, &windowSize2);
    CFRelease(temp);

    AXUIElementCopyAttributeValue(
        frontWindow2, kAXPositionAttribute, (CFTypeRef *)&temp
    );
    AXValueGetValue(temp, kAXValueCGPointType, &windowPosition2);
    CFRelease(temp);



    /**
     * Get app3's front most window.
     */
    AXUIElementCopyAttributeValue(
        app3, kAXFocusedWindowAttribute, (CFTypeRef *)&frontWindow3
    );

    /* Get the title of the window */
    AXUIElementCopyAttributeValue(
        frontWindow3, kAXTitleAttribute, (CFTypeRef *)&windowTitle3
    );

    /* Get the window size and position */
    AXUIElementCopyAttributeValue(
        frontWindow3, kAXSizeAttribute, (CFTypeRef *)&temp
    );
    AXValueGetValue(temp, kAXValueCGSizeType, &windowSize3);
    CFRelease(temp);

    AXUIElementCopyAttributeValue(
        frontWindow3, kAXPositionAttribute, (CFTypeRef *)&temp
    );
    AXValueGetValue(temp, kAXValueCGPointType, &windowPosition3);
    CFRelease(temp);

    //
    printf("\n");
    printf("OK, those three windows will now be locked to size and position\n");
    printf("Press ctrl-c to exit\n");

    // maintain the window sizes and positions until this application is closed
    while (true) {
        pos1 = AXValueCreate(kAXValueCGPointType, &windowPosition1);
        AXUIElementSetAttributeValue(frontWindow1, kAXPositionAttribute, pos1);

        size1 = AXValueCreate(kAXValueCGSizeType, &windowSize1);
        AXUIElementSetAttributeValue(frontWindow1, kAXSizeAttribute, size1);

        pos2 = AXValueCreate(kAXValueCGPointType, &windowPosition2);
        AXUIElementSetAttributeValue(frontWindow2, kAXPositionAttribute, pos2);

        size2 = AXValueCreate(kAXValueCGSizeType, &windowSize2);
        AXUIElementSetAttributeValue(frontWindow2, kAXSizeAttribute, size2);

        pos3 = AXValueCreate(kAXValueCGPointType, &windowPosition3);
        AXUIElementSetAttributeValue(frontWindow3, kAXPositionAttribute, pos3);

        size3 = AXValueCreate(kAXValueCGSizeType, &windowSize3);
        AXUIElementSetAttributeValue(frontWindow3, kAXSizeAttribute, size3);
    }

    // CFRelease(temp);
    CFRelease(pos1);
    CFRelease(pos2);
    CFRelease(pos3);
    CFRelease(size1);
    CFRelease(size2);
    CFRelease(size3);

    /* Clean up */
    CFRelease(frontWindow1);
    CFRelease(frontWindow2);
    CFRelease(frontWindow3);
    CFRelease(app1);
    CFRelease(app2);
    CFRelease(app3);

    // end
    return 0;
}